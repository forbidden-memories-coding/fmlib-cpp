// Rank.h

#ifndef RANK_H
#define RANK_H

#include "Export.hpp"

enum DropType
{
    SAPOW,
    SATEC,
    BCDPOW
};
struct Rank
{
    int SaPow[722] = {0};
    int BcdPow[722] = {0};
    int SaTec[722] = {0};
};

extern "C" EXPORT int* CALL_CONV GetDropType(Rank* rank, DropType type);
 
#endif // RANK_H