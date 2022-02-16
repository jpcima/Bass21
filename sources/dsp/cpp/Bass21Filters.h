#pragma once
#include "FilterTransfer.h"
#include <memory>
#include <iosfwd>
#include <cstdint>

TF2d makePresence(double sampleRate, double param);
TF2d makeDrive(double sampleRate, double param);
TF3d makeRCNetwork1(double sampleRate);
TF2d makeRCNetwork2(double sampleRate);
TF6d makeEQ(double sampleRate, double bass, double treble);

//------------------------------------------------------------------------------
struct FilterCache : std::enable_shared_from_this<FilterCache> {
    using Ptr = std::shared_ptr<FilterCache>;

    enum { TableSize = 128 };

    TF2f presence[TableSize];
    TF2f drive[TableSize];
    TF3f rcNetwork1;
    TF2f rcNetwork2;
    TF6f eq[TableSize][TableSize]; // [bass][treble]
};

//------------------------------------------------------------------------------
FilterCache::Ptr getFilterCache(uint32_t sampleRate);

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const FilterCache &fc);
