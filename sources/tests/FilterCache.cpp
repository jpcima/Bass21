#include "dsp/cpp/Bass21Filters.h"
#include "dsp/cpp/Filter.h"
#include <chrono>
#include <iostream>
namespace kro = std::chrono;

int main()
{
    uint32_t sampleRate = 44100;

    kro::steady_clock::time_point t1, t2;

    t1 = kro::steady_clock::now();
    FilterCache::Ptr fc = getFilterCache(sampleRate);
    t2 = kro::steady_clock::now();

    //
    std::cout << *fc;

    //
    double duration = kro::duration<double>(t2 - t1).count();
    std::cerr << "The filter cache is computed in " << (1e3 * duration) << " ms.\n";

    return 0;
}
