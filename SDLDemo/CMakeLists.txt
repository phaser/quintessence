cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "SDLDemo")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KRAL_PATH})
project (${PROJ_NAME})
include (main)

if (OSX)
    set (BUILD_TYPE MACOSX_BUNDLE)
elseif (WIN32)
	set (BUILD_TYPE WIN32)
elseif (IOS)
    set (BUILD_TYPE MACOSX_BUNDLE)
    set_global_target_property(XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 5.0) 
endif ()

if (WEB)
    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

module(${PROJ_NAME}
        MODULE_TYPE ${BUILD_TYPE}
        DEPENDENCY  SDL2                2.0.0
        DEPENDENCY  QUI2D               dev
        DEPENDENCY  glm                 0.9.6.3
        DEPENDENCY  QUIUtils            dev
        DEPENDENCY  QUIOpenGLES         dev
        DEPENDENCY  QUIRenderer         dev
        DEPENDENCY  QUIInput            dev
        DEPENDENCY  QUIReflection       dev
        DEPENDENCY  QUIVirtualFS        dev
        DEPENDENCY  QUIResourceLoader   dev
        DEPENDENCY  QUIGameEntry        dev
        DEPENDENCY  QUIText             dev
)
        
#if (SHARED_LIB)
#    make_shared_library(${PROJ_NAME})
#else ()
#    build_module(${PROJ_NAME} ${BUILD_TYPE})
#endif ()

if (IOS)
    SET_TARGET_PROPERTIES(${PROJ_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/SDLDemo.plist")
    SET_TARGET_PROPERTIES(${PROJ_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    SET_TARGET_PROPERTIES(${PROJ_NAME} PROPERTIES XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS "Yes")
    SET (CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
    SET (CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
elseif (WEB)
    # Find a list of files and pass them as compile time parameters for this program
    file (GLOB_RECURSE ASSETS "${CMAKE_CURRENT_BINARY_DIR}/assets/*")
    foreach (asset ${ASSETS})
        string (REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" asset "${asset}")
        set (ASSETS_FLAGS "${ASSETS_FLAGS} --preload ${asset}")
    endforeach()
    message ("Preloaded: ${ASSETS_FLAGS}")
    exec_program ("\"${CMAKE_COMMAND}\" -E chdir ${CMAKE_BINARY_DIR} python ~/programe/emsdk_portable/emscripten/1.22.0/tools/file_packager.py resources.res ${ASSETS_FLAGS} > load_resources.js")
  
endif ()
