#include "Core.h"
#include "Bass21Definitions.h"
#if defined(USE_FAUST_DSP)
#include "dsp/Bass21Faust.hxx"
#else
#include "dsp/Bass21Cpp.h"
#endif
#include <DenormalDisabler.h>
#include <cstdio>
#include <cstring>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <Oversampler.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#if defined(USE_FAUST_DSP)
using DSP = Bass21FaustDSP;
#else
using DSP = Bass21CppDSP;
#endif

struct Bass21::Impl {
    double sampleRate_ = 44100.0;
    int effectiveOvsFactorLog2_ = -1;
    bool suspended_ = false;
    float bypassFade_ = 0.0;
    //
    bool bypass_ = false;
    int quality_ = 0;
    //
    DSP dsp_;
    iplug::OverSampler<float> ovs_;
    //
    float copyBuffer_[kMaxFramesPerSegment];
};

Bass21::Bass21()
    : impl_(new Impl)
{
}

Bass21::~Bass21()
{
}

void Bass21::init()
{
    Impl &impl = *impl_;
    DSP &dsp = impl.dsp_;
    dsp.init(impl.sampleRate_);
}

void Bass21::clear()
{
    Impl &impl = *impl_;
    DSP &dsp = impl.dsp_;
#if defined(USE_FAUST_DSP)
    dsp.instanceConstants(impl.sampleRate_);
    dsp.instanceClear();
    dsp.setBegin(true);
#else
    dsp.init(impl.sampleRate_);
#endif

    impl.ovs_.Reset();
    impl.effectiveOvsFactorLog2_ = -1;
    impl.suspended_ = false;
    impl.bypassFade_ = impl.bypass_;
}

void Bass21::setSampleRate(double sampleRate)
{
    Impl &impl = *impl_;
    impl.sampleRate_ = sampleRate;
    clear();
}

void Bass21::run(const float *input, float *output, int numFrames)
{
    WebCore::DenormalDisabler denormalDisabler;

    ///
    Impl &impl = *impl_;
    DSP &dsp = impl.dsp_;
    const double sampleRate = impl.sampleRate_;
    const int quality = impl.quality_;
    iplug::OverSampler<float> &ovs = impl.ovs_;

    //TODO optimize log2
    int desiredFactorLog2 = (int)std::ceil(std::log2(44100.0 * (1 << quality) / sampleRate));
    int maxFactorLog2 = (int)iplug::k8x;

    int factorLog2 = desiredFactorLog2;
    factorLog2 = (factorLog2 < 0) ? 0 : factorLog2;
    factorLog2 = (factorLog2 > maxFactorLog2) ? maxFactorLog2 : factorLog2;

    if (factorLog2 != impl.effectiveOvsFactorLog2_) {
#if defined(USE_FAUST_DSP)
        dsp.instanceConstants(sampleRate * (1 << factorLog2));
        dsp.instanceClear();
        dsp.setBegin(true);
#else
        dsp.init(sampleRate * (1 << factorLog2));
#endif
        ovs.SetOverSampling((iplug::EFactor)factorLog2);
        impl.effectiveOvsFactorLog2_ = factorLog2;
    }

    ///
    const bool bypass = impl.bypass_;
    float bypassFade = impl.bypassFade_;

    for (int frameOffset = 0; frameOffset < numFrames; ) {
        const float *inputWithOffset = input + frameOffset;
        float *outputWithOffset = output + frameOffset;
        int numFramesOfSegment = std::min((int)kMaxFramesPerSegment, numFrames - frameOffset);

        if (bypass && bypassFade == 1.0f) {
            if (input != output)
                std::memcpy(outputWithOffset, inputWithOffset, (unsigned)(numFrames - frameOffset) * sizeof(float));
            frameOffset = numFrames;
            impl.suspended_ = true;
            break;
        }
        if (impl.suspended_)
            clear();

        ///
        bool fading = bypass != bypassFade;
        float *copyBuffer = impl.copyBuffer_;
        if (fading)
            std::memcpy(copyBuffer, inputWithOffset, (unsigned)numFramesOfSegment * sizeof(float));

        ///
        ovs.ProcessBlock(
            (float **)&inputWithOffset, &outputWithOffset, numFramesOfSegment, 1, 1,
            [&dsp](float **inputs, float **outputs, int numSamples) {
                dsp.compute(numSamples, inputs, outputs);
            });

        ///
        constexpr float fadeDelay = kFadeDelayMs * 1e-3f;
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

#if defined(USE_FAUST_DSP)
    dsp.setBegin(false);
#endif

    impl.bypassFade_ = bypassFade;
}

void Bass21::setBypass(bool value)
{
    impl_->bypass_ = value;
}

#define PARAM_SET(X)                            \
    void Bass21::set##X(float value)            \
    {                                           \
        impl_->dsp_.set##X(value);              \
    }

PARAM_SET(Pregain)
PARAM_SET(Level)
PARAM_SET(Blend)
PARAM_SET(Presence)
PARAM_SET(Drive)
PARAM_SET(Bass)
PARAM_SET(Treble)

#undef PARAM_SET

void Bass21::setQuality(int value)
{
    impl_->quality_ = value;
}
