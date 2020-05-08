#ifndef DISCPATCHER_H
#define DISCPATCHER_H

#include "Export.hpp"
#include "Extern.hpp"

#include <string>
#include <fstream>
#include <vector>

namespace FMLib
{
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
}

#endif // DISCPATCHER_H