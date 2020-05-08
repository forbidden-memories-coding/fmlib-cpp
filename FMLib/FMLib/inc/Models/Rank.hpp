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
    int SaPow[722];
    int SaTec[722];
    int BcdPow[722];
    
    int* GetDropType(DropType type);
};

#endif // RANK_H