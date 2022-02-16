#pragma once
#include <iostream>
#include <cstdint>

template <class Real, uint32_t Ord>
struct TF
{
    static_assert(Ord >= 1, "Invalid filter order");

    //--------------------------------------------------------------------------
    Real coef[2 * (Ord + 1)] {};

    //--------------------------------------------------------------------------
    Real *b() noexcept { return coef; }
    Real *a() noexcept { return coef + Ord + 1; }
    const Real *b() const noexcept { return coef; }
    const Real *a() const noexcept { return coef + Ord + 1; }

    //--------------------------------------------------------------------------
    TF<Real, Ord> normalized() const noexcept
    {
        TF<Real, Ord> res;
        const Real a0 = a()[0];
        for (uint32_t i = 0, n = 2 * (Ord + 1); i < n; ++i)
            res.coef[i] = coef[i] / a0;
        return res;
    }

    //--------------------------------------------------------------------------
    template <class Real2> TF<Real2, Ord> to() const noexcept
    {
        TF<Real2, Ord> res;
        for (uint32_t i = 0, n = 2 * (Ord + 1); i < n; ++i)
            res.coef[i] = (Real2)coef[i];
        return res;
    }
};

//------------------------------------------------------------------------------
template <class Real, uint32_t Ord>
std::ostream &operator<<(std::ostream &os, const TF<Real, Ord> &tf)
{
    os << "b=[";
    for (uint32_t i = 0; i <= Ord; ++i)
        os << (i ? " " : "") << tf.b()[i];
    os << "];\n" "a=[";
    for (uint32_t i = 0; i <= Ord; ++i)
        os << (i ? " " : "") << tf.a()[i];
    os << "];\n";
    return os;
}

//------------------------------------------------------------------------------
using TF2d = TF<double, 2>;
using TF3d = TF<double, 3>;
using TF4d = TF<double, 4>;
using TF5d = TF<double, 5>;
using TF6d = TF<double, 6>;

//------------------------------------------------------------------------------
using TF2f = TF<float, 2>;
using TF3f = TF<float, 3>;
using TF4f = TF<float, 4>;
using TF5f = TF<float, 5>;
using TF6f = TF<float, 6>;

//------------------------------------------------------------------------------
TF2d bilinearTransform2(const TF2d &atf, double sampleRate, double warpFactor);
TF3d bilinearTransform3(const TF3d &atf, double sampleRate, double warpFactor);
TF6d bilinearTransform6(const TF6d &atf, double sampleRate, double warpFactor);
