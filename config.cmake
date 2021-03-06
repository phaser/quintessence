add_target (__DEFAULT
    KRAL_PATH       "${CMAKE_CURRENT_LIST_DIR}/KRAL/" 
    PACKAGE_DIRS    "${CMAKE_CURRENT_LIST_DIR}/packages;${CMAKE_CURRENT_LIST_DIR}/thirdparty"  
    PROJECTS_ROOT   "${CMAKE_CURRENT_LIST_DIR}/projects"
    PLATFORM        osx
    PROJECT_DIR     ${CMAKE_CURRENT_LIST_DIR}/SDLDemo
    BUILD_DIR       SDLDemo
    PROJECT_TYPE    "Unix Makefiles"
    BUILD_TYPE      debug
)

add_target (SDLDemo-qt
    INHERIT         __DEFAULT
    PLATFORM        qt5
    PROJECT_TYPE    "Unix Makefiles"
    CUSTOM_ARGS     "-Wdev"
        "-DRUNTIME_DIR=${CMAKE_CURRENT_LIST_DIR}/projects/SDLDemo"
    COMPILER_ARGS_DEBUG
        "-g -O0 -Wall -DPLATFORM_QT5" 
    COMPILER_ARGS_RELEASE
        "-O4 -Wall -DPLATFORM_QT5"
)

add_target (SDLDemo-osx
    INHERIT         __DEFAULT
    PLATFORM        osx
    PROJECT_TYPE    Xcode
    CUSTOM_ARGS
        "-Wdev"
        " -DRUNTIME_DIR=debug"
        " -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\""
        " -DTARGETSDK=MacOSX10.9.sdk"
        " -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD=c++11"
        " -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY=libc++" 
        " -DTESTS=True"
    COMPILER_ARGS_DEBUG
        "-g -O0 -Wall -DPLATFORM_OSX -std=c++11 -stdlib=libc++" 
    COMPILER_ARGS_RELEASE
        "-O4 -Wall -DPLATFORM_OSX -std=c++11 -stdlib=libc++"
)

add_target (SDLDemo-web
    INHERIT         __DEFAULT
    PLATFORM        web
    PROJECT_TYPE    "Unix Makefiles"
    COMPILER_ARGS_DEBUG
        "-Wno-warn-absolute-paths"
        " -g -O0 -Wall -DPLATFORM_WEB" 
    COMPILER_ARGS_RELEASE
        "-Wno-warn-absolute-paths"
        " -O4 -Wall -DPLATFORM_WEB"
    CUSTOM_ARGS     -Wdev
    CUSTOM_ARGS_PD  "-DCMAKE_TOOLCHAIN_FILE=${KRAL_PATH}/Emscripten.cmake"
)

add_target (SDLDemo-osx-lib
    INHERIT         __DEFAULT
    PLATFORM        osx
    PROJECT_TYPE    Xcode
    CUSTOM_ARGS
        "-Wdev"
        " -DRUNTIME_DIR=debug"
        " -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\""
        " -DSHARED_LIB=1"
    COMPILER_ARGS_DEBUG
        "-g -O0 -Wall -DPLATFORM_OSX -std=c++11 -stdlib=libc++" 
    COMPILER_ARGS_RELEASE
        "-O4 -Wall -DPLATFORM_OSX -std=c++11 -stdlib=libc++"
)

add_target (editor-osx
    INHERIT         __DEFAULT
    PLATFORM        osx
    PROJECT_TYPE    Xcode
    PROJECT_DIR     ${CMAKE_CURRENT_LIST_DIR}/editor
    BUILD_DIR       editor
    GEN_CMAKELISTS  True
    CUSTOM_ARGS
        "-Wdev"
        " -DRUNTIME_DIR=debug"
        " -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\""
        " -DTARGETSDK=MacOSX10.10.sdk"
        " -DQT5=1"
)

add_target (SDLDemo-iossim
    INHERIT         __DEFAULT
    PLATFORM        ios
    PROJECT_TYPE    Xcode
    CUSTOM_ARGS
        "-Wdev"
        " -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs\""
        " -DTARGETSDK=iPhoneSimulator7.0.sdk "
)

add_target (SDLDemo-android
    INHERIT         __DEFAULT
    PLATFORM        android
    PROJECT_TYPE    "Unix Makefiles"
    CUSTOM_ARGS
        "-Wdev"
        " -DANDROID_APP_NAME=SDLDemo"
        " -DANDROID_APP_PACKAGE=ro.qui.apps"
    CUSTOM_ARGS_PD
        " -DCMAKE_TOOLCHAIN_FILE=${KRAL_PATH}/android-cmake/android.toolchain.cmake"
        " -DANDROID_NDK=$ENV{NDK}"
        " -DANDROID_ABI=\"armeabi-v7a\""
        " -DANDROID_NATIVE_API_LEVEL=android-19"
        " -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang3.5"
    COMPILER_ARGS_DEBUG   
        "-g -O0 -std=c++11 -DPLATFORM_ANDROID"
    COMPILER_ARGS_RELEASE
        "-O4 -std=c++11 -DPLATFORM_ANDROID"
)
