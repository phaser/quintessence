# Copyright (C) 2011-2012 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIImage")
PROJECT (${PROJ_NAME})


#add_module_dependency(${PROJ_NAME} "libpng" "1.5.10")
add_module_dependency(${PROJ_NAME} "lodepng" "20120729")
add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")
add_module_dependency(${PROJ_NAME} "QUIOpenGLES" "dev")
add_module_dependency(${PROJ_NAME} "QUIVirtualFS" "dev")

make_library(${PROJ_NAME})

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

link_module_dependencies(${PROJ_NAME})

