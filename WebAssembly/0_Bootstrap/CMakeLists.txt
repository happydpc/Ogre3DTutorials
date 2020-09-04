
find_package(ZLIB REQUIRED)
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)

set(MEDIA_DIR "${CMAKE_BINARY_DIR}/0_Bootstrap/media/")

set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_EXE_LINKER_FLAGS "--preload-file ${MEDIA_DIR}/@. -s USE_SDL=2")

add_definitions(-s USE_SDL=2)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASSERTIONS=1 -s DISABLE_EXCEPTION_CATCHING=0")

add_executable(0_Bootstrap Bootstrap.cpp)
target_link_libraries(0_Bootstrap OgreBites ${OGRE_LIBRARIES})

file(COPY
    "media" 
    DESTINATION "${CMAKE_BINARY_DIR}/0_Bootstrap")
    
file(COPY
    "${OGRE_SDK_DIR}/share/OGRE/Media/packs/SdkTrays.zip"
    "${OGRE_SDK_DIR}/share/OGRE/Media/packs/Sinbad.zip"
    DESTINATION ${MEDIA_DIR})

file(COPY
    "${OGRE_SDK_DIR}/share/OGRE/Media/RTShaderLib/GLSL"
    "${OGRE_SDK_DIR}/share/OGRE/Media/RTShaderLib/materials"
    DESTINATION "${MEDIA_DIR}/RTShaderLib/")

file(COPY
    "${OGRE_SDK_DIR}/share/OGRE/Media/ShadowVolume"
    DESTINATION "${MEDIA_DIR}/")
