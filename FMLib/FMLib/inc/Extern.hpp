// Extern.h: Here are the definitions of everything we extern to 3rd party applications
#ifndef EXTERN_H
#define EXTERN_H

#include "Models/Models.hpp"

struct Data
{
    Card    Cards[722];
    Duelist Duelists[39];
    char*   BinPath;
    char*   SlusPath;
    char*   MrgPath;
};

struct IFMLib{};

extern "C" EXPORT Data* CALL_CONV LoadData(IFMLib* lib);
extern "C" EXPORT bool CALL_CONV PatchImage(IFMLib* lib, const char* imgName);
extern "C" EXPORT void CALL_CONV SaveChanges(IFMLib* lib);
extern "C" EXPORT void CALL_CONV WriteData(IFMLib* lib, const Data& dat);
extern "C" EXPORT void CALL_CONV FreeData(IFMLib* lib);
extern "C" EXPORT void CALL_CONV SetBin(IFMLib* lib, const char* newPath);
extern "C" EXPORT const char* CALL_CONV GetBinPath(IFMLib* lib);
extern "C" EXPORT const char* CALL_CONV GetSlusPath(IFMLib* lib);
extern "C" EXPORT const char* CALL_CONV GetMrgPath(IFMLib* lib);

struct IDiscPatcher{};

extern "C" EXPORT void CALL_CONV SetSlus(IDiscPatcher* patcher, const char* newPath);
extern "C" EXPORT void CALL_CONV SetMrg(IDiscPatcher* patcher, const char* newPath);

extern "C" EXPORT IFMLib* CALL_CONV GetLibBin(const char* binPath);
extern "C" EXPORT IFMLib* CALL_CONV GetLibMrgSlus(const char* slusPath, const char* mrgPath);
extern "C" EXPORT IDiscPatcher* CALL_CONV GetPatcher(const char* bin, const char* slus = "", const char* mrg = "");

#endif // EXTERN_H
