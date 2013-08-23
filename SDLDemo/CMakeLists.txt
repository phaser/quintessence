cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "SDLDemo")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KRAL_PATH})
project (${PROJ_NAME})
include (KRALMain)

if (OSX)
    set (BUILD_TYPE MACOSX_BUNDLE CACHE INTERNAL "Build type" FORCE)
endif ()

build_module(${PROJ_NAME} ${BUILD_TYPE})
