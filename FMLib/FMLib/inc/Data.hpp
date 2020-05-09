// Data.h : For all the data game has, for internal use only due to std::map usage

#ifndef DATA_H
#define DATA_H

#include "Models/Models.hpp"

#include "Export.hpp"
#include "Extern.hpp"

#include <map>

typedef unsigned short BYTE;

struct InternalData
{
    InternalData(Data* gameData);
    Data*                   gameData;
    std::map<BYTE, char>    Dict;
    std::map<char, BYTE>    RDict;
};

#endif //DATA_H