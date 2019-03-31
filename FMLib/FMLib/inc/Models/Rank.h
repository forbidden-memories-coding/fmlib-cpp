// Rank.h

#ifndef RANK_H
#define RANK_H

#include "Export.h"

namespace FMLib
{
    enum DropType
    {
        SAPOW,
        SATEC,
        BCDPOW
    };

    namespace Models
    {
        struct EXPORT Rank
        {
            int SaPow[722] = {0};
            int SaTec[722] = {0};
            int BcdPow[722] = {0};

            int* GetDropType(DropType type);
            
        };
    }
}
#endif // RANK_H