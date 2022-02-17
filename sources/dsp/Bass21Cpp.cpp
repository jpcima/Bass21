#include "Bass21Cpp.h"
#include "Bass21Definitions.h"
#include "cpp/Filter.h"
#include "cpp/Bass21Tables.h"
#include "LinearSmoother.hpp"
#include <array>
#include <cassert>

class Bass21CppDSP::Impl {
public:
    float m_sampleRate = 0;

    FilterCache::Ptr m_filters;

    // saturation
    TanhTable *m_tableTanh = &TanhTable::get();

    // filters
    IIR_TF2f<3> m_rcNetwork1;
    IIR_TF2f<2> m_presence;
    IIR_TF2f<2> m_drive;
    IIR_TF2f<3> m_camelFilter;
    IIR_TF2f<2> m_rcNetwork2;
    IIR_TF2f<2> m_simpleActive1;
    //IIR_TF2f<6> m_eq;
    IIR_TF2f<6> m_eq;

    LinearSmoother m_Pregain;
    LinearSmoother m_Level;
    LinearSmoother m_Blend;
    LinearSmoother m_Presence;
    LinearSmoother m_Drive;
    LinearSmoother m_Bass;
    LinearSmoother m_Treble;

    std::array<LinearSmoother *, 7> getSmoothers()
    {
        return {{&m_Pregain, &m_Level, &m_Blend, &m_Presence,
                 &m_Drive, &m_Bass, &m_Treble}};
    }
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
    Impl &impl = *m_impl;

    for (LinearSmoother *s : impl.getSmoothers()) {
        s->setSampleRate(sampleRate);
        s->setTimeConstant(10e-3);
    }

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

    impl.m_rcNetwork1.clear();
    impl.m_presence.clear();
    impl.m_drive.clear();
    impl.m_camelFilter.clear();
    impl.m_rcNetwork2.clear();
    impl.m_simpleActive1.clear();
    impl.m_eq.clear();

    for (LinearSmoother *s : impl.getSmoothers())
        s->clearToTarget();
}

//------------------------------------------------------------------------------
static void applySmoothGain(LinearSmoother &gain, const float *in, float *out, uint32_t count)
{
    float value = gain.getCurrentValue();
    if (value == gain.getTarget()) {
        for (uint32_t i = 0; i < count; ++i)
            out[i] = in[i] * value;
    }
    else {
        for (uint32_t i = 0; i < count; ++i)
            out[i] = in[i] * gain.next();
    }
}

static void applySmoothBlend(LinearSmoother &blend, const float *in1, const float *in2, float *out, uint32_t count)
{
    float value = blend.getCurrentValue();
    if (value == blend.getTarget()) {
        for (uint32_t i = 0; i < count; ++i)
            out[i] = in1[i] + value * (in2[i] - in1[i]);
    }
    else {
        for (uint32_t i = 0; i < count; ++i)
            out[i] = in1[i] + blend.next() * (in2[i] - in1[i]);
    }
}

//------------------------------------------------------------------------------
void Bass21CppDSP::compute(int count_, float const *const *inputs, float *const *outputs)
{
    Impl &impl = *m_impl;
    const uint32_t count = (uint32_t)count_;
    const float *input = inputs[0];

    //--------------------------------------------------------------------------
    // dry blend path

    // pregain
    float dryBlend[kMaxFramesPerSegment];
    applySmoothGain(impl.m_Pregain, input, dryBlend, count);

    // negligible input filter
    ;

    //--------------------------------------------------------------------------
    // wet blend path
    float wetBlend[kMaxFramesPerSegment];

    assert(impl.m_filters);
    FilterCache &filters = *impl.m_filters;
    TanhTable &tableTanh = *impl.m_tableTanh;

    impl.m_rcNetwork1.setTransfer(filters.rcNetwork1);
    impl.m_rcNetwork1.process(dryBlend, wetBlend, count);

    //TODO: smooth presence
    impl.m_presence.setTransfer(filters.getPresence(impl.m_Presence.getTarget()));
    impl.m_presence.processInPlace(wetBlend, count);
    for (uint32_t i = 0; i < count; ++i)
        wetBlend[i] = tableTanh(wetBlend[i]);

    //TODO: smooth drive
    impl.m_drive.setTransfer(filters.getDrive(impl.m_Drive.getTarget()));
    impl.m_drive.processInPlace(wetBlend, count);
    for (uint32_t i = 0; i < count; ++i)
        wetBlend[i] = tableTanh(wetBlend[i]);

    impl.m_camelFilter.setTransfer(filters.camelFilter);
    impl.m_camelFilter.processInPlace(wetBlend, count);

    impl.m_rcNetwork2.setTransfer(filters.rcNetwork2);
    impl.m_rcNetwork2.processInPlace(wetBlend, count);

    impl.m_simpleActive1.setTransfer(filters.simpleActive1);
    impl.m_simpleActive1.processInPlace(wetBlend, count);

    // negligible HPF
    ;

    //--------------------------------------------------------------------------
    // blend mix

    float *output = outputs[0];

    applySmoothBlend(impl.m_Blend, dryBlend, wetBlend, output, count);
    applySmoothGain(impl.m_Level, output, output, count);

    // negligible active filter 2, replaced by volume boost and inversion
    for (uint32_t i = 0; i < count; ++i) {
        for (uint32_t i = 0; i < count; ++i)
            output[i] *= -2.2; // -R2/R1 ; R1=10k, R2=22k
    }
    for (uint32_t i = 0; i < count; ++i)
        output[i] = tableTanh(output[i]);

    //TODO: smooth EQ
    {
        TF6f eqTf = filters.getEQ(impl.m_Bass.getTarget(), impl.m_Treble.getTarget());
        //std::cerr << eqTf;
        impl.m_eq.setTransfer(eqTf);
        impl.m_eq.processInPlace(output, count);
        for (uint32_t i = 0; i < count; ++i)
            output[i] = tableTanh(output[i]);
    }

    // negligible HPF
    ;
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
