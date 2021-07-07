// SPDX-License-Identifier: BSD-2-Clause
#include "Processor.h"
#include "Editor.h"
#include "dsp/Bass21.hxx"
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <Oversampler.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

struct Processor::Impl {
    explicit Impl(Processor *self) : self_(self), vts_(setupParameters()) {}
    std::unique_ptr<juce::AudioProcessorValueTreeState> setupParameters();

    //==========================================================================
    Processor *self_ = nullptr;
    std::unique_ptr<juce::AudioProcessorValueTreeState> vts_;
    Bass21 dsp_;
    iplug::OverSampler<float> ovs_;
    int effectiveOvsFactorLog2_ = -1;
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
    dsp.init(44100);
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
    iplug::OverSampler<float> &ovs = impl.ovs_;

    dsp.instanceConstants(sampleRate);
    dsp.instanceClear();

    ovs.Reset();
    impl.effectiveOvsFactorLog2_ = -1;
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

    juce::ScopedNoDenormals noDenormals;

    Impl &impl = *impl_;
    Bass21 &dsp = impl.dsp_;
    iplug::OverSampler<float> &ovs = impl.ovs_;
    juce::AudioProcessorValueTreeState &vts = *impl.vts_;

    struct {
        float pregain;
        float level;
        float blend;
        float presence;
        float drive;
        float bass;
        float treble;
        int quality;
    } param;

    param.pregain = vts.getRawParameterValue("pregain")->load(std::memory_order_relaxed);
    param.level = vts.getRawParameterValue("level")->load(std::memory_order_relaxed);
    param.blend = vts.getRawParameterValue("blend")->load(std::memory_order_relaxed);
    param.presence = vts.getRawParameterValue("presence")->load(std::memory_order_relaxed);
    param.drive = vts.getRawParameterValue("drive")->load(std::memory_order_relaxed);
    param.bass = vts.getRawParameterValue("bass")->load(std::memory_order_relaxed);
    param.treble = vts.getRawParameterValue("treble")->load(std::memory_order_relaxed);
    param.quality = (int)vts.getRawParameterValue("quality")->load(std::memory_order_relaxed);

    //TODO optimize log2
    double sampleRate = getSampleRate();
    int desiredFactorLog2 = (int)std::ceil(std::log2(44100.0 * param.quality / sampleRate));
    int maxFactorLog2 = (int)iplug::kNumFactors - 1;

    int factorLog2 = juce::jlimit(0, maxFactorLog2, desiredFactorLog2);
    if (factorLog2 != impl.effectiveOvsFactorLog2_) {
        dsp.instanceConstants(sampleRate * (1 << factorLog2));
        dsp.instanceClear();
        ovs.SetOverSampling((iplug::EFactor)factorLog2);
        impl.effectiveOvsFactorLog2_ = factorLog2;
    }

#if 0
    fprintf(
        stderr,
        "level=%.3f blend=%.3f presence=%.3f drive=%.3f bass=%.3f treble=%.3f quality=%d\n",
        param.level, param.blend, param.presence, param.drive, param.bass, param.treble, param.quality);
#endif

    dsp.setPregain(param.pregain);
    dsp.setLevel(param.level);
    dsp.setBlend(param.blend);
    dsp.setPresence(param.presence);
    dsp.setDrive(param.drive);
    dsp.setBass(param.bass);
    dsp.setTreble(param.treble);

    int numSamples = buffer.getNumSamples();
    const float **inputs = buffer.getArrayOfReadPointers();
    float **outputs = buffer.getArrayOfWritePointers();

    ovs.ProcessBlock(
        (float **)inputs, outputs, numSamples, 1, 1,
        [&dsp](float** inputs, float** outputs, int numSamples) {
            dsp.compute(numSamples, inputs, outputs);
        });

#if 0
    fprintf(stderr, "%f\n", buffer.getWritePointer(0)[0]);
#endif
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
static const char StateIdentifier[] = "GROOVY";

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

    return std::make_unique<juce::AudioProcessorValueTreeState>(
        *self,
        nullptr,
        juce::Identifier("PARAMETERS"),
        juce::AudioProcessorValueTreeState::ParameterLayout{
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
            std::make_unique<juce::AudioParameterChoice>(
                "quality",
                "Quality",
                juce::StringArray{"Low", "Medium", "High", "Very high"},
                2),
        });
}

//==============================================================================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new Processor;
}
