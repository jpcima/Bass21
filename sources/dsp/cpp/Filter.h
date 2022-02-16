#pragma once
#include "FilterTransfer.h"
#include <array>

// IIR transposed form II
template <class Real, uint32_t Ord>
class IIR_TF2 {
public:
    void setTransfer(const TF<Real, Ord> &tf)
    {
        m_tf = tf.normalized();
    }

    void clear()
    {
        m_mem.fill(Real(0));
    }

    template <class Sample>
    void process(const Sample *in, Sample *out, std::size_t count)
    {
        const Real *a = m_tf.a();
        const Real *b = m_tf.b();
        std::array<Real, Ord> mem = m_mem;

        for (std::size_t frameno = 0; frameno < count; ++frameno) {
            Real x = (Real)in[frameno];
            Real y = b[0] * x + mem[0];
            for (uint32_t i = 1; i < Ord; ++i)
                 mem[i - 1] = mem[i] + b[i] * x - a[i] * y;
            mem[Ord - 1] = b[Ord] * x - a[Ord] * y;
            out[frameno] = (Sample)y;
        }

        m_mem = mem;
    }

    template <class Sample>
    void processInPlace(Sample *inout, std::size_t count)
    {
        process(inout, inout, count);
    }

private:
    std::array<Real, Ord> m_mem{};
    TF<Real, Ord> m_tf;
};
