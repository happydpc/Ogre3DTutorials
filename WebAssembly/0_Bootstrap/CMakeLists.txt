
find_package(ZLIB REQUIRED)
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)

set(CMAKE_EXECUTABLE_SUFFIX ".html")
# set(CMAKE_EXE_LINKER_FLAGS "--preload-file ${MEDIA_DIR}/@. -s BINARYEN_TRAP_MODE=clamp -s EXPORTED_FUNCTIONS=\"['_passAssetAsArrayBuffer', '_clearScene', '_main']\" -s USE_SDL=2")
set(CMAKE_EXE_LINKER_FLAGS " -s USE_SDL=2")

add_definitions(-s USE_SDL=2)

if(TRUE)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASSERTIONS=1 -s DISABLE_EXCEPTION_CATCHING=0")
endif()

add_executable(0_Bootstrap Bootstrap.cpp)
target_link_libraries(0_Bootstrap OgreBites ${OGRE_LIBRARIES})
#set_target_properties(0_Bootstrap PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s WASM=1 --bind")
