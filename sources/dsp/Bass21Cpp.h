#pragma once
#include <memory>

class Bass21CppDSP {
public:
    Bass21CppDSP();
    ~Bass21CppDSP();

    void init(double sampleRate);
    void clear();
    void compute(int count, float const *const *inputs, float *const *outputs);

    //--------------------------------------------------------------------------
    float getPregain() const;
    void setPregain(float value);

    float getLevel() const;
    void setLevel(float value);

    float getBlend() const;
    void setBlend(float value);

    float getPresence() const;
    void setPresence(float value);

    float getDrive() const;
    void setDrive(float value);

    float getBass() const;
    void setBass(float value);

    float getTreble() const;
    void setTreble(float value);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
