<a href="https://ogrecave.github.io/ogre/api/1.10/tutorials.html"><img src="https://ogrecave.github.io/ogre/api/1.10/ogre-logo-wetfloor.gif" title="Ogre3D" alt="https://codrer.com/swap/2016/ogre_logo.svg"></a>


# Ogre3DTutorials

> Includes all tutorials for Ogre3D built with CMake and llvm on OSX using VSCode

> C++ Ogre3D VSCode CMake llvm OSX

# Setup
You will need to follow these [steps](https://ogrecave.github.io/ogre/api/latest/building-ogre.html) to build Ogre3D engine for your platform using CMake. But as of Ogre3D version `1.12.8` you will want to review the following notes before running any of the commands.

## Native OSX Platform
 - When building on Ogre3D natively on OSX you will need `OGRE_ENABLE_PRECOMPILED_HEADERS` to `OFF` as well as turing off un-needed compoments. See [this](https://forums.ogre3d.org/viewtopic.php?f=2&p=548230) for details. Not doing so causes this error:
 >error: Objective-C was disabled in PCH file but is currently enabled
 - These are the commands:
 ```
 mkdir build
 cd build
 export CMAKE_INSTALL_PREFIX=[EmSDKPath]
 cmake .. -DCMAKE_BUILD_TYPE=Release cmake .. -DCMAKE_BUILD_TYPE=Release -DOGRE_ENABLE_PRECOMPILED_HEADERS=OFF -DOGRE_BUILD_COMPONENT_JAVA=FALSE -DOGRE_BUILD_ANDROID_JNI_SAMPLE=FALSE -DOGRE_BUILD_COMPONENT_PYTHON=FALSE -DOGRE_BUILD_COMPONENT_CSHARP=FALSE -DCMAKE_INSTALL_PREFIX=[EmSDKPath]
 make -j18
 make install
 cd [EmSDKPath]
 ln -s [EmSDKPath]/lib/macosx/Release lib/Release
 ```
 

## WebAssembly Emscripten Platform
- Download and install [emscripten](https://github.com/emscripten-core/emscripten). As of Ogre3D version `1.12.8` you will need to modify the following to get a succesfull build environment:
  - When using any version of emscripten later than `1.39.0` will need to modify `/Samples/Emscripten/CMakeLists.txt` before you can build the Ogre3D for webassembly. Remove this `-s BINARYEN_TRAP_MODE=clamp` see [issue](https://github.com/OGRECave/ogre/issues/1686) for details.
  - The build instructions suggest that you should create a cmake build folder named `build-wasm`. Unfortunatly doing so will produce and error during `emmake make install` action as install expects the build output folder to have been called `build`
  
  >CMake Error at cmake_install.cmake:97 (file):
  >file INSTALL cannot find
  >"/Users/gbranco/personal/ogre/build/CMakeFiles/Export/lib/OGRE/cmake/OgreTargets.cmake":
  >No such file or directory.
  
  - Given that the Emscripten build of Ogre3dD crosscompiles some of its dependencies in (i.e libzzip and freetype) you will want to override the default install path `/usr/local`. As such you will probably want to override the install path on cmake.
  ```
  ##[ modify `/Samples/Emscripten/CMakeLists.txt` see above]
  pushd [emsdkDir]
  source emsdk_env.sh
  popd
  mkdir build
  cd build
  export CMAKE_INSTALL_PREFIX=[EmSDKPath]
  emcmake cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=[EmSDKPath]
  emmake make -j18
  emmake make install

  ```  

- Next clone this repo on your machine and copy both sdks folders produced by the ogre3d build(s) on to this repo.
