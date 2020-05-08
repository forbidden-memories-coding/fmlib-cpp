// FMLib.h : Includes all of the public API
#ifndef FMLIB_H
#define FMLIB_H

#include "DataReader.hpp"
#include "DiscPatcher.hpp"
#include "Data.hpp"
#include "Extern.hpp"

namespace FMLib
{
    class FMLib : public IFMLib
    {
    public:
        explicit  FMLib(const std::string& binPath);
        FMLib(const std::string& slusPath, const std::string& mrgPath);
        ~FMLib();

        Data*   LoadData();
        bool    PatchImage(const char* imgName);
        void    WriteData(const Data& dat);
        void    FreeData();
        void    SaveChanges();

        void  SetBin(const char* newPath);

        const char* GetBinPath();
        const char* GetSlusPath();
        const char* GetMrgPath();

    private:
        void  ExtractFiles();

    private:
        struct Chunk
        {
            char syncPattern[12];
            char address[3];
            char mode;
            char subheader[8];
            char data[2048]; // 2048 is raw data size
            char errorDetect[4];
            char errorCorrection[276];
        };

    private:
        _Data           m_data;
        DiscPatcher     m_patcher;
        DataReader      m_reader;
        std::fstream    m_bin;
        std::fstream    m_slus;
        std::fstream    m_mrg;
        std::string     m_binPath;
        std::string     m_slusPath;
        std::string     m_mrgPath;
    };
}

#endif // FMLIB_H