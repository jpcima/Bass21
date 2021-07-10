#pragma once
#include "dsp/Bass21.hxx"
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <Oversampler.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

class Bass21 {
public:
    void init();
    void clear();
    void setSampleRate(double sampleRate);
    void run(const float *input, float *output, int numFrames);

    void setPregain(float value) { dsp_.setPregain(value); }
    void setLevel(float value) { dsp_.setLevel(value); }
    void setBlend(float value) { dsp_.setBlend(value); }
    void setPresence(float value) { dsp_.setPresence(value); }
    void setDrive(float value) { dsp_.setDrive(value); }
    void setBass(float value) { dsp_.setBass(value); }
    void setTreble(float value) { dsp_.setTreble(value); }
    void setQuality(int value) { quality_ = value; }

private:
    double sampleRate_ = 44100.0;
    int effectiveOvsFactorLog2_ = -1;
    int quality_ = 0;
    Bass21DSP dsp_;
    iplug::OverSampler<float> ovs_;
};
