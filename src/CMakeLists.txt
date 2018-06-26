cmake_minimum_required(VERSION 2.6)

project(ProjetRO)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

add_executable(ProjetRO main.cpp
                        SharedElements.h SharedElements.cpp
                        costFunctions.h costFunctions.cpp
                        moveMaster.h moveMaster.cpp
                        heuristique.h heuristique.cpp
                        localSearch.h localSearch.cpp
                        shotgun.h shotgun.cpp)

