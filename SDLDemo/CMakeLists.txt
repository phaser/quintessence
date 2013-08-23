cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "SDLDemo")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KRAL_PATH})
project (${PROJ_NAME})
include (KRALMain)

if (OSX)
    set (BUILD_TYPE MACOSX_BUNDLE CACHE INTERNAL "Build type" FORCE)
endif ()

add_module_dependency(${PROJ_NAME} "SDL2" "2.0.0")
add_module_dependency(${PROJ_NAME} "QUIGameEntry" "dev")

build_module(${PROJ_NAME} ${BUILD_TYPE})

link_module_dependencies(${PROJ_NAME})
