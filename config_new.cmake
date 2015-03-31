add_target ("__DEFAULT"
    KRAL_PATH       "${CMAKE_CURRENT_LIST_DIR}/KRAL/" 
    PACKAGE_DIRS    "${CMAKE_CURRENT_LIST_DIR}/packages;${CMAKE_CURRENT_LIST_DIR}/thirdparty"  
    PROJECTS_ROOT   "${CMAKE_CURRENT_LIST_DIR}/projects"
    PLATFORM        "osx"
    PROJECT_TYPE    "Unix Makefiles"
)

# SDLDemo-osx
add_target("SDLDemo-osx"
    PLATFORM        "osx"
    PROJECT_DIR     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo"
    BUILD_DIR       "SDLDemo"
    PROJECT_TYPE    "Xcode"
    BUILD_TYPE      "debug"    
    CUSTOM_ARGS
        "-Wdev"
        " -DRUNTIME_DIR=debug"
        " -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\""
        " -DTARGETSDK=MacOSX10.9.sdk"
)
