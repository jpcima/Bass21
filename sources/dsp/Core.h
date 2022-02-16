#pragma once
#include <memory>

class Bass21 {
public:
    Bass21();
    ~Bass21();

    void init(double sampleRate);
    void clear();
    void setSampleRate(double sampleRate);
    void run(const float *input, float *output, int numFrames);

    void setBypass(bool value);
    void setPregain(float value);
    void setLevel(float value);
    void setBlend(float value);
    void setPresence(float value);
    void setDrive(float value);
    void setBass(float value);
    void setTreble(float value);
    void setQuality(int value);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
