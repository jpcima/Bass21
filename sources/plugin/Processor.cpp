// SPDX-License-Identifier: BSD-2-Clause
#include "Processor.h"
#include "Editor.h"
#include "dsp/Core.h"

struct Processor::Impl {
    explicit Impl(Processor *self) : self_(self), vts_(setupParameters()) {}
    std::unique_ptr<juce::AudioProcessorValueTreeState> setupParameters();

    //==========================================================================
    Processor *self_ = nullptr;
    std::unique_ptr<juce::AudioProcessorValueTreeState> vts_;
    Bass21 dsp_;

    //==========================================================================
    struct {
        std::atomic<float> *bypass;
        std::atomic<float> *pregain;
        std::atomic<float> *level;
        std::atomic<float> *blend;
        std::atomic<float> *presence;
        std::atomic<float> *drive;
        std::atomic<float> *bass;
        std::atomic<float> *treble;
        std::atomic<float> *quality;
    } param_;
    juce::RangedAudioParameter *bypassParameter_ = nullptr;
};

//==============================================================================
Processor::Processor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::mono())
                     .withOutput("Output", juce::AudioChannelSet::mono())),
    impl_(new Impl(this))
{
    Impl &impl = *impl_;
    Bass21 &dsp = impl.dsp_;
    dsp.init();
}

Processor::~Processor()
{
}

//==========================================================================
juce::AudioProcessorValueTreeState &Processor::getValueTreeState()
{
    Impl &impl = *impl_;
    return *impl.vts_;
}

//==============================================================================
void Processor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    (void)samplesPerBlock;

    Impl &impl = *impl_;
    Bass21 &dsp = impl.dsp_;

    dsp.setSampleRate(sampleRate);
}

void Processor::releaseResources()
{
}

bool Processor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    juce::AudioChannelSet inputs = layouts.getMainInputChannelSet();
    juce::AudioChannelSet outputs = layouts.getMainOutputChannelSet();

    return inputs == juce::AudioChannelSet::mono() &&
        outputs == juce::AudioChannelSet::mono();
}

void Processor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    (void)midiMessages;
    bool isForcedBypass = false;
    processBlockInternally(buffer, isForcedBypass);
}

void Processor::processBlockBypassed(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    //NOTE: documentation promises this will not get called when there is a
    //      custom bypass parameter, in practice it is not the case.
    (void)midiMessages;
    bool isForcedBypass = true;
    processBlockInternally(buffer, isForcedBypass);
}

void Processor::processBlockInternally(juce::AudioBuffer<float> &buffer, bool isForcedBypass)
{
    Impl &impl = *impl_;

    juce::ScopedNoDenormals noDenormals;
    Bass21 &dsp = impl.dsp_;

    bool bypass = isForcedBypass || impl.param_.bypass->load(std::memory_order_relaxed) >= 0.5f;
    float pregain = impl.param_.pregain->load(std::memory_order_relaxed);
    float level = impl.param_.level->load(std::memory_order_relaxed);
    float blend = impl.param_.blend->load(std::memory_order_relaxed);
    float presence = impl.param_.presence->load(std::memory_order_relaxed);
    float drive = impl.param_.drive->load(std::memory_order_relaxed);
    float bass = impl.param_.bass->load(std::memory_order_relaxed);
    float treble = impl.param_.treble->load(std::memory_order_relaxed);
    int quality = (int)impl.param_.quality->load(std::memory_order_relaxed);

    dsp.setBypass(bypass);
    dsp.setPregain(pregain);
    dsp.setLevel(level);
    dsp.setBlend(blend);
    dsp.setPresence(presence);
    dsp.setDrive(drive);
    dsp.setBass(bass);
    dsp.setTreble(treble);
    dsp.setQuality(quality);

    dsp.run(buffer.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
}

//==============================================================================
juce::AudioProcessorEditor *Processor::createEditor()
{
    return new Editor(*this);
}

bool Processor::hasEditor() const
{
    return true;
}

//==============================================================================
const juce::String Processor::getName() const
{
    return JucePlugin_Name;
}

bool Processor::acceptsMidi() const
{
    return false;
}

bool Processor::producesMidi() const
{
    return false;
}

bool Processor::isMidiEffect() const
{
    return false;
}

double Processor::getTailLengthSeconds() const
{
    return 0.0;
}

juce::AudioProcessorParameter *Processor::getBypassParameter() const
{
    Impl &impl = *impl_;
    return impl.bypassParameter_;
}

//==============================================================================
int Processor::getNumPrograms()
{
    return 1;
}

int Processor::getCurrentProgram()
{
    return 0;
}

void Processor::setCurrentProgram(int index)
{
    (void)index;
}

const juce::String Processor::getProgramName(int index)
{
    (void)index;
    return {};
}

void Processor::changeProgramName(int index, const juce::String &newName)
{
    (void)index;
    (void)newName;
}

//==============================================================================
void Processor::getStateInformation(juce::MemoryBlock &destData)
{
    Impl &impl = *impl_;
    juce::AudioProcessorValueTreeState &vts = *impl.vts_;
    juce::ValueTree state = vts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Processor::setStateInformation(const void *data, int sizeInBytes)
{
    Impl &impl = *impl_;
    juce::AudioProcessorValueTreeState &vts = *impl.vts_;
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState && xmlState->hasTagName(vts.state.getType()))
        vts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
std::unique_ptr<juce::AudioProcessorValueTreeState> Processor::Impl::setupParameters()
{
    Processor *self = self_;

    std::unique_ptr<juce::AudioProcessorValueTreeState> vts(
        new juce::AudioProcessorValueTreeState(
            *self,
            nullptr,
            juce::Identifier("PARAMETERS"),
            juce::AudioProcessorValueTreeState::ParameterLayout{
                std::make_unique<juce::AudioParameterBool>(
                    "bypass",
                    "Bypass",
                    false),
                std::make_unique<juce::AudioParameterFloat>(
                    "pregain",
                    "Pregain",
                    0.0f,
                    2.0f,
                    1.0f),
                std::make_unique<juce::AudioParameterFloat>(
                    "level",
                    "Level",
                    0.0f,
                    1.0f,
                    0.5f),
                std::make_unique<juce::AudioParameterFloat>(
                    "blend",
                    "Blend",
                    0.0f,
                    1.0f,
                    0.5f),
                std::make_unique<juce::AudioParameterFloat>(
                    "presence",
                    "Presence",
                    0.0f,
                    1.0f,
                    0.5f),
                std::make_unique<juce::AudioParameterFloat>(
                    "drive",
                    "Drive",
                    0.0f,
                    1.0f,
                    0.5f),
                std::make_unique<juce::AudioParameterFloat>(
                    "bass",
                    "Bass",
                    0.0f,
                    1.0f,
                    0.5f),
                std::make_unique<juce::AudioParameterFloat>(
                    "treble",
                    "Treble",
                    0.0f,
                    1.0f,
                    0.5f),
                /* NOTE: marking as non-automatable troubles Ardour6 */
                std::make_unique<juce::AudioParameterChoice>(
                    "quality",
                    "Quality",
                    juce::StringArray{"Low", "Medium", "High", "Very high"},
                    2),
            }));

    param_.bypass = vts->getRawParameterValue("bypass");
    param_.pregain = vts->getRawParameterValue("pregain");
    param_.level = vts->getRawParameterValue("level");
    param_.blend = vts->getRawParameterValue("blend");
    param_.presence = vts->getRawParameterValue("presence");
    param_.drive = vts->getRawParameterValue("drive");
    param_.bass = vts->getRawParameterValue("bass");
    param_.treble = vts->getRawParameterValue("treble");
    param_.quality = vts->getRawParameterValue("quality");

    bypassParameter_ = vts->getParameter("bypass");

    return vts;
}

//==============================================================================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new Processor;
}
