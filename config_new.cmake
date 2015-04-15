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
    CUSTOM_ARGS     -Wdev
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
)

add_target (SDLDemo-web
    INHERIT         __DEFAULT
    PLATFORM        web
    PROJECT_TYPE    "Unix Makefiles"
    COMPILER_ARGS   "-Wno-warn-absolute-paths"
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
)

add_target (editor-osx
    INHERIT         __DEFAULT
    PLATFORM        osx
    PROJECT_TYPE    Xcode
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
