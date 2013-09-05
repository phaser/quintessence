# Copyright (C) 2011-2012 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIVirtualFS")
PROJECT (${PROJ_NAME})


add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")
add_module_dependency(${PROJ_NAME} "zlib" "1.2.5")
add_module_dependency(${PROJ_NAME} "libzip" "0.9.3")
IF (DEFINED TESTS)
    add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
    add_module_dependency(${PROJ_NAME} "gtest-entrypoint" "dev")
ENDIF (DEFINED TESTS)

make_library(${PROJ_NAME})

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC ${STOP_ON_ERRORS}")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

link_module_dependencies(${PROJ_NAME})

IF (DEFINED TESTS)
    IF (LINUX)
        TARGET_LINK_LIBRARIES (${PROJ_NAME} "pthread")
    ENDIF (LINUX)
ENDIF (DEFINED TESTS)
