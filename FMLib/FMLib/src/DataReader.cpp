#include "DataReader.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>
#include <cstring>

namespace FMLib
{
    static std::string GetText(std::fstream& f, const std::map<BYTE, char>& dic)
    {
        std::string res = "";

        while (true)
        {
            char b;
            f.read(&b, 1);
            BYTE b_num = b;

            if (dic.find(b_num) != dic.end())
            {
                res += dic.at(b_num);
            }
            else if (b_num == 65534)
            {
                res += "\r\n";
            }
            else
            {
                if (b_num == 65535)
                    break;

                std::stringstream ss;
                ss << std::setfill('0') << std::setw(2) << std::hex << b_num;
                res += "[" + ss.str() + "]";
            }
            
        }

        return res;
    }

    void DataReader::LoadDataFromSlus(std::fstream& slus, _Data& dat)
    {
        // General card data
        slus.seekg(0x1C4A44);
        for (int i = 0; i < 722; ++i)
        {
            int cardDataPacked = ReadType<int>(slus);

            dat.gameData.Cards[i].Id = i + 1;
            dat.gameData.Cards[i].Attack = (cardDataPacked & 0x1FF) * 10; // Unwrap attack value
            dat.gameData.Cards[i].Defense = (cardDataPacked >> 9 & 0x1FF) * 10; // Unwrap defense value
            dat.gameData.Cards[i].GuardianStar_Primary = cardDataPacked >> 18 & 0xF; // Unwrap 1st guardian star
            dat.gameData.Cards[i].GuardianStar_Secondary = cardDataPacked >> 22 & 0xF; // Unwrap 2nd guardian star
            dat.gameData.Cards[i].Type = cardDataPacked >> 26 & 0x1F; // Unwrap card's type
        }

        std::cout << dat.gameData.Cards[0].Attack << "\n";

        std::cout << "Loaded general cards data...\n";

        // Cards level and attribute
        slus.seekg(0x1C5B33L);
        for (int i = 0; i < 722; ++i)
        {
            unsigned char levelAttrPack = ReadType<unsigned char>(slus);
            dat.gameData.Cards[i].Level = levelAttrPack & 0xF; // Unwrap card level
            dat.gameData.Cards[i].Attribute = levelAttrPack >> 4 & 0xF; // Unwrap card's attribute
        }

        std::cout << "Loaded cards level and attribute...\n";

        // Card name
        for(int i = 0; i < 722; ++i)
        {
            slus.seekg(0x1C6002 + i * 2);
            unsigned short num = ReadType<unsigned short>(slus);
            slus.seekg(0x1C6800 + num - 0x6000);
            auto cardName = GetText(slus, dat.Dict);
            dat.gameData.Cards[i].Name = new char[cardName.size() + 1]; // TODO: Check if any leaks occur
            strcpy_s(dat.gameData.Cards[i].Name, cardName.size() + 1, cardName.c_str());
            // dat.gameData.Cards[i].Name = GetText(slus, dat.Dict).c_str();
        }

        std::cout << "Loaded cards names...\n";
        
        // Card description
        for(int i = 0; i < 722; ++i)
        {
            slus.seekg(0x1B0A02 + i * 2);
            unsigned short off = ReadType<unsigned short>(slus);
            slus.seekg(0x1B11F4 + (off - 0x9F4));
            auto cardDesc = GetText(slus, dat.Dict);
            dat.gameData.Cards[i].Description = new char[cardDesc.size() + 1]; // TODO: Check if any leaks occur
            strcpy_s(dat.gameData.Cards[i].Description, cardDesc.size() + 1, cardDesc.c_str());
            // dat.gameData.Cards[i].Description = GetText(slus, dat.Dict);
        }

        std::cout << "Loaded cards descriptions...\n";

        // Duelist names
        for(int i = 0; i < 39; ++i)
        {
            slus.seekg(0x1C6652 + i * 2);
            slus.seekg(0x1C6800 + ReadType<unsigned short>(slus) - 0x6000);
            auto duelName = GetText(slus, dat.Dict);
            auto nameAlloc = new char[duelName.size() + 1]; // TODO: Check if any leaks occur
            std::cout << "Duelist name: " << duelName << "\n";
            std::cout << "Loop index: " << i << "\n";
            strcpy_s(nameAlloc, duelName.size() + 1, duelName.c_str());
            // dat.gameData.Duelists[i].Name = nameAlloc;
            auto duelist = Duelist();
            dat.gameData.Duelists[i] = duelist;
            dat.gameData.Duelists[i].Name = nameAlloc;
        }

        std::cout << "Loaded duelists names...\n";
        
    }

    void DataReader::LoadDataFromWaMrg(std::fstream& mrg, _Data& dat)
    {
        // Fusions
        mrg.seekg(0xB87800);
        unsigned char fuseDat[0x10000];
        ReadType(mrg, fuseDat, sizeof(unsigned char) * 0x10000);

        for(int i = 0; i < 722; ++i)
        {
            long position = 2 + i * 2;
            int fusionIndex = 0;
            unsigned char posDat[2];
            posDat[0] = fuseDat[position];
            posDat[1] = fuseDat[position + 1];
            unsigned short num = static_cast<unsigned short>(posDat[1] << 8 | posDat[0]);
            position = num & 0xFFFF;

            if (position != 0)
            {
                int fusionAmt = fuseDat[position++];
                if (fusionAmt == 0)
                {
                    fusionAmt = 511 - fuseDat[position++];
                }

                int num2 = fusionAmt;
                dat.gameData.Cards[i].FusionsAmount = num2;
                dat.gameData.Cards[i].Fusions = new Fusion[num2];

                while (num2 > 0)
                {
                    int num3 = fuseDat[position++];
                    int num4 = fuseDat[position++];
                    int num5 = fuseDat[position++];
                    int num6 = fuseDat[position++];
                    int num7 = fuseDat[position++];
                    int num9 = (num3 & 3) << 8 | num4;
                    int num11 = (num3 >> 2 & 3) << 8 | num5;
                    int num13 = (num3 >> 4 & 3) << 8 | num6;
                    int num15 = (num3 >> 6 & 3) << 8 | num7;

                    auto fusion = Fusion();
                    fusion.Card1 = i + 1;
                    fusion.Card2 = num9 - 1;
                    fusion.Result = num11 - 1;

                    dat.gameData.Cards[i].Fusions[fusionIndex++] = fusion;
                    --num2;

                    if (num2 <= 0) continue;

                    fusion.Card1 = i + 1;
                    fusion.Card2 = num13 - 1;
                    fusion.Result = num15 - 1;

                    dat.gameData.Cards[i].Fusions[fusionIndex++] = fusion;
                    --num2;
                }
            }
        }

        // Equips
        mrg.seekg(0xB85000);
        unsigned char equipDat[0x2800];
        ReadType(mrg, equipDat, sizeof(unsigned char) * 0x2800);

        int position = 0;
        while (true)
        {
            unsigned char num[2];
            num[0] = equipDat[position++];
            num[1] = equipDat[position++];
            unsigned short equipId = static_cast<unsigned short>(num[1] << 8 | num[0]);

            if (equipId == 0)
                break;

            num[0] = equipDat[position++];
            num[1] = equipDat[position++];
            unsigned short monsterNum = static_cast<unsigned short>(num[1] << 8 | num[0]);
            dat.gameData.Cards[equipId - 1].Equips = new int[monsterNum];

            for(int i = 0; i < monsterNum; ++i)
            {
                num[0] = equipDat[position++];
                num[1] = equipDat[position++];
                unsigned short monsterId = static_cast<unsigned short>(num[1] << 8 | num[0]);
                dat.gameData.Cards[equipId - 1].Equips[i] = monsterId - 1;
            }
        }

        // Card costs/passwords
        unsigned char starCost[722 * 8];
        mrg.seekg(0xFB9808, mrg.beg);
        ReadType(mrg, starCost, sizeof(unsigned char) * 722 * 8);

        position = 0;
        for(int i = 0; i < 722; ++i)
        {
            unsigned char cost[4];
            cost[0] = starCost[position++];
            cost[1] = starCost[position++];
            cost[2] = starCost[position++];
            cost[3] = starCost[position++];
            dat.gameData.Cards[i].Starchip.Cost = (cost[3] << 24) | (cost[2] << 16) | (cost[1] << 8) | cost[0];
            unsigned char pass[4];
            pass[0] = starCost[position++];
            pass[1] = starCost[position++];
            pass[2] = starCost[position++];
            pass[3] = starCost[position++];

            std::string resPass;
            for(int j = 3; j >= 0; --j)
            {
                std::stringstream ss;
                ss << std::setfill('0') << std::setw(2) << std::hex << (int)pass[j];
                resPass += ss.str();
            }
            dat.gameData.Cards[i].Starchip.PasswordStr = new char[resPass.size() + 1];
            strcpy_s(dat.gameData.Cards[i].Starchip.PasswordStr, resPass.size() + 1, resPass.c_str());
            dat.gameData.Cards[i].Starchip.Password = (strcmp(resPass.c_str(), "fffffffe") != 0) ? std::stoi(resPass) : 0;
        }
        

        // Read duelist decks and card drops
        for(int i = 0; i < 39; ++i)
        {
            int num = 0xE9B000 + 0x1800 * i;
            mrg.seekg(num);

            unsigned char memStream[1444];

            ReadType(mrg, memStream, 1444);
            position = 0;
            for(int j = 0; j < 722; ++j)
            {
                unsigned char num[2];
                num[0] = memStream[position++];
                num[1] = memStream[position++];
                dat.gameData.Duelists[i].Deck[j] = static_cast<int>(num[1] << 8 | num[0]);
            }

            mrg.seekg(num + 0x5B4);

            ReadType(mrg, memStream, 1444);
            position = 0;
            for(int j = 0; j < 722; ++j)
            {
                unsigned char num[2];
                num[0] = memStream[position++];
                num[1] = memStream[position++];
                dat.gameData.Duelists[i].Drop.SaPow[j] = static_cast<int>(num[1] << 8 | num[0]);
            }

            mrg.seekg(num + 0xB68);

            ReadType(mrg, memStream, 1444);
            position = 0;
            for(int j = 0; j < 722; ++j)
            {
                unsigned char num[2];
                num[0] = memStream[position++];
                num[1] = memStream[position++];
                dat.gameData.Duelists[i].Drop.BcdPow[j] = static_cast<int>(num[1] << 8 | num[0]);
            }

            mrg.seekg(num + 0x111C);

            ReadType(mrg, memStream, 1444);
            position = 0;
            for(int j = 0; j < 722; ++j)
            {
                unsigned char num[2];
                num[0] = memStream[position++];
                num[1] = memStream[position++];
                dat.gameData.Duelists[i].Drop.SaTec[j] = static_cast<int>(num[1] << 8 | num[0]);
            }
        }
    }

    void DataReader::LoadAllData(std::fstream& slus, std::fstream& mrg, _Data& dat)
    {
        std::cout << "Started loading data...\n";
        LoadDataFromSlus(slus, dat);
        std::cout << "Finished loading from SLUS...\n";
        LoadDataFromWaMrg(mrg, dat);
        std::cout << "Finished loading data...\n";
    }
}
