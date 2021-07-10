// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>

class Processor : public juce::AudioProcessor {
public:
    Processor();
    ~Processor() override;

    //==========================================================================
    juce::AudioProcessorValueTreeState &getValueTreeState();

    //==========================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override;
    void processBlock(juce::AudioBuffer<double> &, juce::MidiBuffer &) override { jassertfalse; }
    void processBlockBypassed(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override;
    void processBlockBypassed(juce::AudioBuffer<double> &, juce::MidiBuffer &) override { jassertfalse; }
private:
    void processBlockInternally(juce::AudioBuffer<float> &buffer, bool isForcedBypass);

public:
    //==========================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    //==========================================================================
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    juce::AudioProcessorParameter *getBypassParameter() const override;

    //==========================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==========================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Processor)
};
