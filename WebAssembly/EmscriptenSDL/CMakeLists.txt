
set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_EXE_LINKER_FLAGS " -s USE_SDL=2")
add_definitions(-s USE_SDL=2)
add_executable(SDL2 SDL2.cpp)
