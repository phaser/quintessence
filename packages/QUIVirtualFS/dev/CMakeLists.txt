# Copyright (C) 2011-2012 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIVirtualFS")
PROJECT (${PROJ_NAME})

library(${PROJ_NAME}
        DEPENDENCY "QUIUtils" "dev"
        DEPENDENCY "zlib" "1.2.5"
        DEPENDENCY "libzip" "0.9.3"
)

if (TESTS)
    add_subdirectory(tests)
endif()

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC ${STOP_ON_ERRORS}")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

IF (DEFINED TESTS)
    IF (LINUX)
        TARGET_LINK_LIBRARIES (${PROJ_NAME} "pthread")
    ENDIF (LINUX)
ENDIF (DEFINED TESTS)
