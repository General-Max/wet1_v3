cmake_minimum_required(VERSION 3.21)
project(wet1_v3)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_s_v3 WorldCupTests.cpp
        AVLTree.h
        Player.h
        Player.cpp
        SortById.h
        SortById.cpp
        SortByScore.h
        SortByScore.cpp
        SortTeamById.h
        SortTeamById.cpp
        Team.h
        Team.cpp
        TwoWayList.h
        worldcup23a1.h
        worldcup23a1.cpp
        wet1util.h)
