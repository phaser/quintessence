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

if (QT5)
    MESSAGE(STATUS "on qt5")
    set (CMAKE_INCLUDE_CURRENT_DIR ON)
    set (CMAKE_AUTOMOC ON)
    find_package (Qt5Widgets REQUIRED)
    find_package (Qt5OpenGL REQUIRED)
    qt5_wrap_ui(ui_mainwindow.h "${CMAKE_CURRENT_LIST_DIR}/source/common/mainwindow.ui")
endif ()

add_module_includes(${PROJ_NAME} "QUIGameEntry" "dev")
add_module_includes(${PROJ_NAME} "glm" "0.9.3.3")
add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")

build_module(${PROJ_NAME} ${BUILD_TYPE})

link_module_dependencies(${PROJ_NAME})
if (QT5)
    qt5_use_modules(${PROJ_NAME} Widgets)
    qt5_use_modules(${PROJ_NAME} OpenGL)
endif ()

