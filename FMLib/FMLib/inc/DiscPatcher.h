#ifndef DISCPATCHER_H
#define DISCPATCHER_H

#include "Export.h"
#include "Models/GameFile.h"

#include <string>
#include <fstream>
#include <vector>

#define CHUNK_SIZE 2352
#define DATA_SIZE 2048
// This should be the proper table for CRC32 calculation for all PSX games (from Mednafen-core's github)

namespace FMLib
{
    struct IDiscPatcher
    {
        virtual bool PatchImage(const char* imgName) = 0;
        virtual void SetBin(const char* newPath) = 0;
        virtual void SetSlus(const char* newPath) = 0;
        virtual void SetMrg(const char* newPath) = 0;
    };
    class DiscPatcher : public IDiscPatcher
    {
    public:
             DiscPatcher(const std::string& bin, const std::string& slus = "", const std::string& mrg = "");
        bool PatchImage(const char* imgName);

        void SetBin(const char* newPath);
        void SetSlus(const char* newPath);
        void SetMrg(const char* newPath);

    private:
        std::fstream                    m_binFile;
        std::fstream                    m_slusFile;
        std::fstream                    m_mrgFile;
    };

    extern "C" EXPORT IDiscPatcher* CALL_CONV GetPatcher(const char* bin, const char* slus = "", const char* mrg = "");
}

#endif // DISCPATCHER_H