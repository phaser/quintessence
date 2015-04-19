# Copyright (C) 2011-2012 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIGameEntry")
PROJECT (${PROJ_NAME})

IF (ANDROID)
	EXEC_PROGRAM ("android${CMDEXT} create project --target ${ANDROID_TARGET} --name ${ANDROID_APP_NAME} --path ${CMAKE_CURRENT_BINARY_DIR}/../${PLATFORM} --activity ${ANDROID_APP_NAME}Activity --package ${ANDROID_APP_PACKAGE} ")
ELSEIF (OSX)
    export_ios_framework("Cocoa")
    export_ios_framework("GLKit")
    export_ios_framework("OpenGL")
    export_ios_framework("SDL2")
ELSEIF (QT5)
    MESSAGE(STATUS "on qt5")
    set (CMAKE_INCLUDE_CURRENT_DIR ON)
    set (CMAKE_AUTOMOC ON)
    find_package (Qt5Widgets REQUIRED)
    find_package (Qt5OpenGL REQUIRED)
    qt5_wrap_ui(ui_mainwindow.h "${CMAKE_CURRENT_LIST_DIR}/source/qt5/mainwindow.ui")
    export_ios_framework(OpenGL)
    export_ios_framework(GLKit)
elseif (IOS)
    export_ios_framework(Foundation)
    export_ios_framework(CoreGraphics)
    export_ios_framework(UIKit)
    export_ios_framework(GLKit)
    export_ios_framework(OpenGLES)
    export_ios_framework(AudioToolbox)
    export_ios_framework(QuartzCore)
ENDIF (ANDROID)

library(${PROJ_NAME}
        DEPENDENCY "SDL2" "2.0.0"
        DEPENDENCY "QUIOpenGLES" "dev"
        DEPENDENCY "QUIVirtualFS" "dev"
        DEPENDENCY "QUIInput" "dev"
        DEPENDENCY "glm" "0.9.6.3"
        DEPENDENCY "QUIUtils" "dev"
)

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

if (LINUX)
    target_link_libraries (${PROJ_NAME} "glfw")
elseif (OSX)
elseif (QT5)
    qt5_use_modules(${PROJ_NAME} Widgets)
    qt5_use_modules(${PROJ_NAME} OpenGL)
endif (LINUX)

