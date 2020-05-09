# Start
> FMLib is a C++ library to modify the game "Yu-Gi-Oh! Forbidden Memories" for the PSX

This documentation is still pretty much a work in progress and bound to be incomplete and changing rapidly.

## What is this library supposed to do?

* independent cross platform library
* read, write and modify _data from the game
* provide several functions for game specific tasks

## Requirements

* CMake >= 3
* C++ Compiler (Visual Studio 2017, 2019; GCC; MingW; XCode)

## Project layout

    FMLib/
        CMakeLists.txt # Config file for CMake
        FMLib/
            inc/
                Data.h
                DataReader.h
                DiscPatcher.h
                Export.h
                FMLib.h
                Models/
                    Card.h
                    Duelist.h
                    Fusion.h
                    GameFile.h
                    Rank.h
                    Ritual.h
                    Starchips.h
            src/
                Data.cpp
                DataReader.cpp
                DiscPatcher.cpp
                FMLib.cpp
                Models/
                    Duelist.cpp
                    Fusion.cpp
                    Rank.cpp
