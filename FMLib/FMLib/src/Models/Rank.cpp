#include "Models/Models.hpp"

extern "C" EXPORT int* CALL_CONV GetDropType(Rank* rank, DropType type)
{
    switch (type)
    {
        case DropType::SAPOW:
            return rank->SaPow;

        case DropType::SATEC:
            return rank->SaTec;

        case DropType::BCDPOW:
            return rank->BcdPow;

        default:
            return nullptr;
    }
}