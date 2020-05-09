// GameFile.h

#ifndef GAMEFILE_H
#define GAMEFILE_H

#include "Export.h"

namespace FMLib
{
    namespace Models
    {
        struct EXPORT GameFile
        {
            int     Offset;
            int     Size;
            int     Name;
            int     NameSize;
            bool    IsDirectory;
        };
    }
}
#endif // !GAMEFILE_H
