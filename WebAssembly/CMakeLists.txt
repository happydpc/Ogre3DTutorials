cmake_minimum_required(VERSION 3.3)

set(OGRE_SDK_DIR "${CMAKE_SOURCE_DIR}/../WebAssemblySDK")

project(Ogre3DTutorialsWeb)
set(ZLIB_INCLUDE_DIR "${OGRE_SDK_DIR}/inlcude")
set(ZLIB_LIBRARY "${OGRE_SDK_DIR}/lib/libz.a")
set(OGRE_DIR "${OGRE_SDK_DIR}/lib/OGRE/cmake")

include_directories("${OGRE_SDK_DIR}/inlcude")
link_directories("${OGRE_SDK_DIR}/lib")

add_subdirectory("${CMAKE_SOURCE_DIR}/0_Bootstrap/")
add_subdirectory("${CMAKE_SOURCE_DIR}/EmscriptenTest/")
add_subdirectory("${CMAKE_SOURCE_DIR}/EmscriptenSDL/")
