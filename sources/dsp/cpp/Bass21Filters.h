#pragma once
#include "FilterTransfer.h"
#include <memory>
#include <cstdint>

TF6d makeEQ(double sampleRate, double bass, double treble);

//------------------------------------------------------------------------------
struct FilterCache : std::enable_shared_from_this<FilterCache> {
    using Ptr = std::shared_ptr<FilterCache>;

    enum { TableSize = 128 };
    TF6f eq[TableSize][TableSize]; // [bass][treble]
};

//------------------------------------------------------------------------------
FilterCache::Ptr getFilterCache(uint32_t sampleRate);
