// GameFile.h

#ifndef GAMEFILE_H
#define GAMEFILE_H

struct GameFile
{
    int     Offset;
    int     Size;
    int     Name;
    int     NameSize;
    bool    IsDirectory;
};
#endif // !GAMEFILE_H
