// SPDX-License-Identifier: ISC

#pragma once
#include <cstdint>

class LerpTable {
public:
    LerpTable() = default;
    LerpTable(double (*function)(double), double min, double max, uint32_t numPoints);
    LerpTable(const float *data, double min, double max, uint32_t numPoints, bool copyData);
    template <uint32_t N> LerpTable(const float (&data)[N], double min, double max, bool copyData);
    ~LerpTable();

    float operator()(float x) const noexcept;

private:
    LerpTable(const LerpTable &) = delete;
    LerpTable &operator=(const LerpTable &) = delete;

private:
    uint32_t numPoints_ = 0;
    const float *data_ = nullptr;
    float offset_ = 0;
    float scale_ = 0;
    bool dataOwned_ = false;
};

///
template <uint32_t N>
inline LerpTable::LerpTable(const float (&data)[N], double min, double max, bool copyData)
    : LerpTable(data, min, max, N, copyData)
{
}

inline float LerpTable::operator()(float x) const noexcept
{
    const float *data = data_;
    int32_t numPoints = (int32_t)numPoints_;
    int32_t maxIndex = numPoints - 1;

    float index = (x - offset_) * scale_;
    index = (index > 0) ? index : 0;
    index = (index < (float)maxIndex) ? index : (float)maxIndex;

    int32_t i1 = (int32_t)index;
    int32_t i2 = (i1 + 1 < maxIndex) ? (i1 + 1) : maxIndex;

    float y1 = data[i1];
    float y2 = data[i2];

    float dx = index - (float)i1;
    return y1 + dx * (y2 - y1);
}
