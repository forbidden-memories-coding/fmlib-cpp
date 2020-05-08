// Duelist.h
#ifndef DUELIST_H
#define DUELIST_H

#include "Rank.hpp"

struct Duelist
{
    char*          Name;
    int            Deck[722];
    Rank            Drop;
};
#endif // DUELIST_H
