#include "Extern.hpp"
#include "FMLib.hpp"
#include "DiscPatcher.hpp"
#include <iostream>


extern "C" EXPORT Data* CALL_CONV LoadData(IFMLib* lib)
{
    std::cout << "This is a LoadData call\n";
    auto fmlib = (FMLib::FMLib*)lib;
    auto data = fmlib->LoadData();
    std::cout << "Finished loading data, returning...\n";
    return data;
}

extern "C" EXPORT bool CALL_CONV PatchImage(IFMLib* lib, const char* imgName)
{
    auto fmlib = (FMLib::FMLib*)lib;
    return fmlib->PatchImage(imgName);
}

extern "C" EXPORT void CALL_CONV SaveChanges(IFMLib* lib)
{
    auto fmlib = (FMLib::FMLib*)lib;
    fmlib->SaveChanges();
}

extern "C" EXPORT void CALL_CONV WriteData(IFMLib* lib, const Data& dat)
{
    auto fmlib = (FMLib::FMLib*)lib;
    fmlib->WriteData(dat);
}

extern "C" EXPORT void CALL_CONV FreeData(IFMLib* lib)
{
    auto fmlib = (FMLib::FMLib*)lib;
    fmlib->FreeData();
}

extern "C" EXPORT void CALL_CONV SetBin(IFMLib* lib, const char* newPath)
{
    auto fmlib = (FMLib::FMLib*)lib;
    fmlib->SetBin(newPath);
}

extern "C" EXPORT const char* CALL_CONV GetBinPath(IFMLib* lib)
{
    auto fmlib = (FMLib::FMLib*)lib;
    return fmlib->GetBinPath();
}

extern "C" EXPORT const char* CALL_CONV GetSlusPath(IFMLib* lib)
{
    auto fmlib = (FMLib::FMLib*)lib;
    return fmlib->GetSlusPath();
}

extern "C" EXPORT const char* CALL_CONV GetMrgPath(IFMLib* lib)
{
    auto fmlib = (FMLib::FMLib*)lib;
    return fmlib->GetMrgPath();
}

extern "C" EXPORT void CALL_CONV SetSlus(IDiscPatcher* patcher, const char* newPath)
{
    auto discPatcher = (FMLib::DiscPatcher*)patcher;
    discPatcher->SetSlus(newPath);
}

extern "C" EXPORT void CALL_CONV SetMrg(IDiscPatcher* patcher, const char* newPath)
{
    auto discPatcher = (FMLib::DiscPatcher*)patcher;
    discPatcher->SetMrg(newPath);
}

extern "C" EXPORT IFMLib* CALL_CONV GetLibBin(const char* binPath)
{
    return new FMLib::FMLib(std::string(binPath));
}

extern "C" EXPORT IFMLib* CALL_CONV GetLibMrgSlus(const char* slusPath, const char* mrgPath)
{
    return new FMLib::FMLib(std::string(slusPath), std::string(mrgPath));
}

extern "C" EXPORT IDiscPatcher* CALL_CONV GetPatcher(const char* bin, const char* slus, const char* mrg)
{
    return new FMLib::DiscPatcher(bin, slus, mrg);
}