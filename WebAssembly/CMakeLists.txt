cmake_minimum_required(VERSION 3.3)

project(Ogre3DTutorialsWeb)
set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../WebAssemblySDK/inlcude")
set(ZLIB_LIBRARY "${CMAKE_SOURCE_DIR}/../WebAssemblySDK/lib/libz.a")
include_directories("${CMAKE_SOURCE_DIR}/../WebAssemblySDK/inlcude")
link_directories("${CMAKE_SOURCE_DIR}/../WebAssemblySDK/lib")
set(OGRE_DIR "${CMAKE_SOURCE_DIR}/../WebAssemblySDK/lib/OGRE/cmake/")

add_subdirectory("${CMAKE_SOURCE_DIR}/EmscriptenTest/")
add_subdirectory("${CMAKE_SOURCE_DIR}/0_Bootstrap/")
