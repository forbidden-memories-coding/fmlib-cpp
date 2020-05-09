// Card.h

#ifndef CARD_H
#define CARD_H

#include "Fusion.hpp"
#include "Ritual.hpp"
#include "Starchips.hpp"

struct Card
{
    int                 Id;
    char*               Name;
    char*               Description;
    int                 Attack;
    int                 Defense;
    int                 Attribute;
    int                 Level;
    int                 Type;
    int                 GuardianStar_Primary;
    int                 GuardianStar_Secondary;
    Fusion*             Fusions;
    int                 FusionsAmount;
    int*                Equips;
    int                 EquipsAmount;
    Ritual              Rituals;
    Starchips           Starchip;
};



#endif // CARD_H
