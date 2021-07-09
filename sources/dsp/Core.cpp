#include "Core.h"
#include <cstdio>
#include <cstring>

constexpr int Bass21::maxFramesPerSegment;
constexpr float Bass21::fadeDelay;

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
    suspended_ = false;
    bypassFade_ = bypass_;
}

void Bass21::setSampleRate(double sampleRate)
{
    sampleRate_ = sampleRate;
    clear();
}

void Bass21::run(const float *input, float *output, int numFrames)
{
    const double sampleRate = sampleRate_;
    const int quality = quality_;

    ///
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

    ///
    const bool bypass = bypass_;
    float bypassFade = bypassFade_;

    if (suspended_ && !bypass && bypass == bypassFade) {
        // resume from suspended state
        clear();
    }

    int frameOffset = 0;

    while (frameOffset < numFrames) {
        const float *inputWithOffset = input + frameOffset;
        float *outputWithOffset = output + frameOffset;
        int numFramesOfSegment = std::min(maxFramesPerSegment, numFrames - frameOffset);

        if (bypass && bypassFade == 1.0f) {
            if (input != output)
                std::memcpy(outputWithOffset, inputWithOffset, (unsigned)(numFrames - frameOffset) * sizeof(float));
            frameOffset = numFrames;
            suspended_ = true;
            break;
        }

        ///
        bool fading = bypass != bypassFade;
        float *copyBuffer = copyBuffer_;
        if (fading)
            std::memcpy(copyBuffer, inputWithOffset, (unsigned)numFramesOfSegment * sizeof(float));

        ///
        ovs.ProcessBlock(
            (float **)&inputWithOffset, &outputWithOffset, numFramesOfSegment, 1, 1,
            [&dsp](float **inputs, float **outputs, int numSamples) {
                dsp.compute(numSamples, inputs, outputs);
            });

        ///
        if (fading && bypass) {
            float fadeInc = (1.0f / (float)sampleRate) * (1.0f / fadeDelay);
            for (int i = 0; i < numFramesOfSegment; ++i) {
                outputWithOffset[i] = outputWithOffset[i] * (1.0f - bypassFade) + copyBuffer[i] * bypassFade;
                bypassFade = bypassFade + fadeInc;
                bypassFade = (bypassFade > 1.0f) ? 1.0f : bypassFade;
            }
        }
        else if (fading && !bypass) {
            float fadeInc = (1.0f / (float)sampleRate) * (1.0f / fadeDelay);
            for (int i = 0; i < numFramesOfSegment; ++i) {
                outputWithOffset[i] = outputWithOffset[i] * (1.0f - bypassFade) + copyBuffer[i] * bypassFade;
                bypassFade = bypassFade - fadeInc;
                bypassFade = (bypassFade < 0.0f) ? 0.0f : bypassFade;
            }
        }

        ///
        frameOffset += numFramesOfSegment;
    }

    dsp.setBegin(false);

    bypassFade_ = bypassFade;
}