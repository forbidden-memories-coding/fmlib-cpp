// DataReader.h: Used for reading game's data

#ifndef DATAREADER_H
#define DATAREADER_H

#include "Data.hpp"

#include <fstream>

namespace FMLib
{
    class DataReader
    {
    public:
        DataReader() = default; 

        void LoadDataFromSlus(std::fstream& slus, _Data& dat);
        void LoadDataFromWaMrg(std::fstream& mrg, _Data& dat);
        void LoadAllData(std::fstream& slus, std::fstream& mrg, _Data& dat);

    private:
        template<typename T>
        T ReadType(std::fstream& f);

        template<typename T>
        void ReadType(std::fstream& f, T *data, size_t size);
    };

    template<typename T>
    T DataReader::ReadType(std::fstream& f)
    {
        T obj;
        f.read(reinterpret_cast<char*>(&obj), sizeof(obj));
        return obj;
    }

    template<typename T>
    void DataReader::ReadType(std::fstream& f, T *data, size_t size)
    {
        f.read(reinterpret_cast<char*>(data), size);
    }
}

#endif // DATAREADER_H