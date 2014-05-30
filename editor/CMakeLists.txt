cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "editor")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KRAL_PATH})
project (${PROJ_NAME})
include (KRALMain)

if (OSX)
    set (BUILD_TYPE MACOSX_BUNDLE)
elseif (WIN32)
	set (BUILD_TYPE WIN32)
endif()

add_module_includes(${PROJ_NAME} "QUIGameEntry" "dev")
add_module_includes(${PROJ_NAME} "glm" "0.9.3.3")
add_module_includes(${PROJ_NAME} "QUIUtils" "dev")

build_module(${PROJ_NAME} ${BUILD_TYPE})

