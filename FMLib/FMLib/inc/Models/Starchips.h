// Starchips.h

#ifndef STARCHIPS_H
#define STARCHIPS_H

#include "Export.h"
#include <string>

namespace FMLib
{
    namespace Models
    {
        struct EXPORT Starchips
        {
            int         Cost;
            int         Password;
            std::string PasswordStr;
        };
    }
}
#endif // STARCHIPS_H