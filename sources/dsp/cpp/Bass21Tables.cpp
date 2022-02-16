#include "Bass21Tables.h"

TanhTable::TanhTable()
    : LerpTable(tanh, -4.0, +4.0, 128)
{
}

TanhTable &TanhTable::get()
{
    static TanhTable instance;
    return instance;
}
