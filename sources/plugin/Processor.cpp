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

    //==========================================================================
    struct {
        std::atomic<float> *pregain;
        std::atomic<float> *level;
        std::atomic<float> *blend;
        std::atomic<float> *presence;
        std::atomic<float> *drive;
        std::atomic<float> *bass;
        std::atomic<float> *treble;
        std::atomic<float> *quality;
    } param_;
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

    float pregain = impl.param_.pregain->load(std::memory_order_relaxed);
    float level = impl.param_.level->load(std::memory_order_relaxed);
    float blend = impl.param_.blend->load(std::memory_order_relaxed);
    float presence = impl.param_.presence->load(std::memory_order_relaxed);
    float drive = impl.param_.drive->load(std::memory_order_relaxed);
    float bass = impl.param_.bass->load(std::memory_order_relaxed);
    float treble = impl.param_.treble->load(std::memory_order_relaxed);
    int quality = (int)impl.param_.quality->load(std::memory_order_relaxed);

    //TODO optimize log2
    double sampleRate = getSampleRate();
    int desiredFactorLog2 = (int)std::ceil(std::log2(44100.0 * (1 << quality) / sampleRate));
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
        level, blend, presence, drive, bass, treble, quality);
#endif

    dsp.setPregain(pregain);
    dsp.setLevel(level);
    dsp.setBlend(blend);
    dsp.setPresence(presence);
    dsp.setDrive(drive);
    dsp.setBass(bass);
    dsp.setTreble(treble);

    int sampleOffset = 0;
    int numSamples = buffer.getNumSamples();
    const int maxSamplesPerSegment = 512;

    const float **inputs = buffer.getArrayOfReadPointers();
    float **outputs = buffer.getArrayOfWritePointers();

    while (sampleOffset < numSamples) {
        int numSamplesOfSegment = std::min(maxSamplesPerSegment, numSamples - sampleOffset);

        const float *inputsWithOffset[1] = { inputs[0] + sampleOffset };
        float *outputsWithOffset[1] = { outputs[0] + sampleOffset };

        ovs.ProcessBlock(
            (float **)inputsWithOffset, outputsWithOffset, numSamplesOfSegment, 1, 1,
            [&dsp](float** inputs, float** outputs, int numSamples) {
                dsp.compute(numSamples, inputs, outputs);
            });

        sampleOffset += numSamplesOfSegment;
    }

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
                    juce::StringArray{"Low", "Medium", "High", "Very high", "Best"},
                    2),
            }));

    param_.pregain = vts->getRawParameterValue("pregain");
    param_.level = vts->getRawParameterValue("level");
    param_.blend = vts->getRawParameterValue("blend");
    param_.presence = vts->getRawParameterValue("presence");
    param_.drive = vts->getRawParameterValue("drive");
    param_.bass = vts->getRawParameterValue("bass");
    param_.treble = vts->getRawParameterValue("treble");
    param_.quality = vts->getRawParameterValue("quality");

    return vts;
}

//==============================================================================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new Processor;
}
