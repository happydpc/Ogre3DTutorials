cmake_minimum_required(VERSION 3.1)

project(Ogre3DTutorialsWeb)


#
# Trying usual cmake project compiler execution
#

add_definitions("-std=c++11")
add_subdirectory("${CMAKE_SOURCE_DIR}/EmscriptenTest/")
