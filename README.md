compile
=======

    cmake -P KRAL/build.cmake

Mac OS X
========

 * Install Xcode
 * Get and install SDL2 from http://www.libsdl.org/download-2.0.php
 * Get and install SDL_Image from http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.dmg

Compile the Qt target
=====================

You have to install Qt in order to compile this target and then set CMAKE_PREFIX_PATH to contain the path
to Qt CMake modules. You should export this in your environment.

Example:
    export CMAKE_PREFIX_PATH=/HomeDir/Qt/5.5/clang_64/lib/cmake:$CMAKE_PREFIX_PATH
