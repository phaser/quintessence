cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIGameEntry")
PROJECT (${PROJ_NAME})

#IF (ANDROID)
#	EXEC_PROGRAM ("android${CMDEXT} create project --target ${ANDROID_TARGET} --name ${ANDROID_APP_NAME} --path ${CMAKE_CURRENT_BINARY_DIR}/../${PLATFORM} --activity ${ANDROID_APP_NAME}Activity --package ${ANDROID_APP_PACKAGE} ")
#ELSEIF (OSX)
#    set (CMAKE_INCLUDE_CURRENT_DIR ON)
#    set (CMAKE_AUTOMOC ON)
#    find_package (Qt5Widgets REQUIRED)
#    find_package (Qt5OpenGL REQUIRED)
#    qt5_wrap_ui(ui_mainwindow.h "${CMAKE_CURRENT_LIST_DIR}/source/osx/mainwindow.ui")
#ELSEIF (QT5)
#    MESSAGE(STATUS "on qt5")
#    set (CMAKE_INCLUDE_CURRENT_DIR ON)
#    set (CMAKE_AUTOMOC ON)
#    find_package (Qt5Widgets REQUIRED)
#    find_package (Qt5OpenGL REQUIRED)
#    qt5_wrap_ui(ui_mainwindow.h "${CMAKE_CURRENT_LIST_DIR}/source/qt5/mainwindow.ui")
#ENDIF (ANDROID)

add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")
add_module_dependency(${PROJ_NAME} "SDL2" "2.0.0")

make_library(${PROJ_NAME})

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

link_module_dependencies(${PROJ_NAME})

