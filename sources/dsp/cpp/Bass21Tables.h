#pragma once
#include "LerpTable.h"
#include <cmath>

class TanhTable : public LerpTable {
protected:
    TanhTable();
public:
    static TanhTable &get();
};
