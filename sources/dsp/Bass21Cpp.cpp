#include "Bass21Cpp.h"
#include "LinearSmoother.hpp"

class Bass21CppDSP::Impl {
public:
    float m_sampleRate = 0;

    FilterCache::Ptr m_filters;

    LinearSmoother m_Pregain;
    LinearSmoother m_Level;
    LinearSmoother m_Blend;
    LinearSmoother m_Presence;
    LinearSmoother m_Drive;
    LinearSmoother m_Bass;
    LinearSmoother m_Treble;
};

Bass21CppDSP::Bass21CppDSP()
    : m_impl(new Impl)
{
}

Bass21CppDSP::~Bass21CppDSP()
{
}

void Bass21CppDSP::init(double sampleRate)
{
    

    clear();
}

void Bass21CppDSP::setFilters(FilterCache::Ptr filters)
{
    Impl &impl = *m_impl;

    if (filters == impl.m_filters)
        return;

    impl.m_filters = filters;
    clear();
}

void Bass21CppDSP::clear()
{
    Impl &impl = *m_impl;

    

    impl.m_Pregain.clearToTarget();
    impl.m_Level.clearToTarget();
    impl.m_Blend.clearToTarget();
    impl.m_Presence.clearToTarget();
    impl.m_Drive.clearToTarget();
    impl.m_Bass.clearToTarget();
    impl.m_Treble.clearToTarget();
}

void Bass21CppDSP::compute(int count, float const *const *inputs, float *const *outputs)
{
    
}

//------------------------------------------------------------------------------
#define PARAM_GETSET(X)                         \
    float Bass21CppDSP::get##X() const          \
    {                                           \
        return m_impl->m_##X.getTarget();       \
    }                                           \
    void Bass21CppDSP::set##X(float value)      \
    {                                           \
        m_impl->m_##X.setTarget(value);         \
    }

PARAM_GETSET(Pregain)
PARAM_GETSET(Level)
PARAM_GETSET(Blend)
PARAM_GETSET(Presence)
PARAM_GETSET(Drive)
PARAM_GETSET(Bass)
PARAM_GETSET(Treble)

#undef PARAM_GETSET
