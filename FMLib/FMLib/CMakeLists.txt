cmake_minimum_required(VERSION 3.0)

add_definitions(-DLIBEXPORT)

add_library(
    FMLib SHARED
        "src/FMLib.cpp"
        "src/DataReader.cpp"
        "src/DiscPatcher.cpp"
        "src/Data.cpp"
        "src/Models/Rank.cpp"
        "src/Extern.cpp"
        "inc/FMLib.hpp"
        "inc/Export.hpp"
        "inc/DataReader.hpp"
        "inc/DiscPatcher.hpp"
        "inc/Data.hpp"
        "inc/Models/Card.hpp"
        "inc/Models/Duelist.hpp"
        "inc/Models/Fusion.hpp"
        "inc/Models/GameFile.hpp"
        "inc/Models/Rank.hpp"
        "inc/Models/Ritual.hpp"
        "inc/Models/Starchips.hpp"
)

target_include_directories(
    FMLib 
        PUBLIC "inc"
        PUBLIC "Models"
)

