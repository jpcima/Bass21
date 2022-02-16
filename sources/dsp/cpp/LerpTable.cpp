// SPDX-License-Identifier: ISC

#include "LerpTable.h"
#include <memory>
#include <cstring>

LerpTable::LerpTable(double (*function)(double), double min, double max, uint32_t numPoints)
{
    std::unique_ptr<float[]> data{new float[numPoints]};

    for (uint32_t i = 0; i < numPoints; ++i) {
        double x = min + i * ((max - min) / (double)(numPoints - 1));
        data[i] = (float)function(x);
    }

    numPoints_ = numPoints;
    offset_ = (float)min;
    scale_ = (float)((double)(numPoints - 1) / (max - min));
    data_ = data.release();
    dataOwned_ = true;
}

LerpTable::LerpTable(const float *data, double min, double max, uint32_t numPoints, bool copyData)
{
    numPoints_ = numPoints;
    offset_ = (float)min;
    scale_ = (float)((double)(numPoints - 1) / (max - min));

    if (!copyData) {
        data_ = data;
        dataOwned_ = false;
    }
    else {
        float *dataCopy = new float[numPoints];
        std::memcpy(dataCopy, data, numPoints * sizeof(float));
        data_ = dataCopy;
        dataOwned_ = true;
    }
}

LerpTable::~LerpTable()
{
    if (dataOwned_)
        delete[] data_;
}
