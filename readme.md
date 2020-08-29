<a href="https://ogrecave.github.io/ogre/api/1.10/tutorials.html"><img src="https://ogrecave.github.io/ogre/api/1.10/ogre-logo-wetfloor.gif" title="Ogre3D" alt="https://codrer.com/swap/2016/ogre_logo.svg"></a>


# Ogre3DTutorials

> Includes all tutorials for Ogre3D built with CMake and llvm on OSX using VSCode

> C++ Ogre3D VSCode CMake llvm OSX

### Setup

- First follow these [steps](https://ogrecave.github.io/ogre/api/latest/building-ogre.html) to build Ogre3D engine for platform using CMake. Also download and install [emscripten](https://github.com/emscripten-core/emscripten) and build another sdk for WebAssembly. Note due to an issue with the latest version of emscripten you may need to modify /Samples/Emscripten/CMakeLists.txt b/Samples/Emscripten/CMakeLists.txt before us can build the Ogre3D for webassemble. Remove this `-s BINARYEN_TRAP_MODE=clamp` from the CMakeLists.txt see [issue](https://github.com/OGRECave/ogre/issues/1686)

- Next clone this repo on your machine and copy both sdks folders produced by the ogre3d build(s) on to this repo.
