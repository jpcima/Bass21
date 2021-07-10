#include "Core.h"
#include <cstring>

void Bass21::init()
{
    Bass21DSP &dsp = dsp_;
    dsp.init(sampleRate_);
}

void Bass21::clear()
{
    Bass21DSP &dsp = dsp_;
    dsp.instanceConstants(sampleRate_);
    dsp.instanceClear();
    dsp.setBegin(true);

    ovs_.Reset();
    effectiveOvsFactorLog2_ = -1;
}

void Bass21::setSampleRate(double sampleRate)
{
    sampleRate_ = sampleRate;
    clear();
}

void Bass21::run(const float *input, float *output, int numFrames)
{
    double sampleRate = sampleRate_;
    int quality = quality_;

    if (bypass_) {
        //TODO clean bypass
        if (input != output)
            std::memcpy(output, input, (unsigned)numFrames * sizeof(float));
        return;
    }

    Bass21DSP &dsp = dsp_;
    iplug::OverSampler<float> &ovs = ovs_;

    //TODO optimize log2
    int desiredFactorLog2 = (int)std::ceil(std::log2(44100.0 * (1 << quality) / sampleRate));
    int maxFactorLog2 = (int)iplug::k8x;

    int factorLog2 = desiredFactorLog2;
    factorLog2 = (factorLog2 < 0) ? 0 : factorLog2;
    factorLog2 = (factorLog2 > maxFactorLog2) ? maxFactorLog2 : factorLog2;

    if (factorLog2 != effectiveOvsFactorLog2_) {
        dsp.instanceConstants(sampleRate * (1 << factorLog2));
        dsp.instanceClear();
        dsp.setBegin(true);
        ovs.SetOverSampling((iplug::EFactor)factorLog2);
        effectiveOvsFactorLog2_ = factorLog2;
    }

    int sampleOffset = 0;
    const int maxSamplesPerSegment = 512;

    while (sampleOffset < numFrames) {
        int numSamplesOfSegment = std::min(maxSamplesPerSegment, numFrames - sampleOffset);

        const float *inputsWithOffset[1] = { input + sampleOffset };
        float *outputsWithOffset[1] = { output + sampleOffset };

        ovs.ProcessBlock(
            (float **)inputsWithOffset, outputsWithOffset, numSamplesOfSegment, 1, 1,
            [&dsp](float** inputs, float** outputs, int numSamples) {
                dsp.compute(numSamples, inputs, outputs);
            });

        sampleOffset += numSamplesOfSegment;
    }

    dsp.setBegin(false);
}
