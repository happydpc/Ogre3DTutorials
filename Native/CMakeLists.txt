cmake_minimum_required(VERSION 3.10)
project(Ogre3DTutorials)

# required for Ogre 1.12+
set(CMAKE_CXX_STANDARD 11)

set(OGRE_DIR "${CMAKE_SOURCE_DIR}/../OsxSDK/CMake/")

find_package(PkgConfig)
find_package(PkgConfig REQUIRED)

add_subdirectory("${CMAKE_SOURCE_DIR}/0_Bootstrap/")
