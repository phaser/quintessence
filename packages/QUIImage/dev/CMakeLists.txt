# Copyright (C) 2011-2012 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIImage")
PROJECT (${PROJ_NAME})

library(${PROJ_NAME}
        DEPENDENCY "lodepng" "20120729"
        DEPENDENCY "QUIUtils" "dev"
        DEPENDENCY "QUIOpenGLES" "dev"
        DEPENDENCY "QUIVirtualFS" "dev"
)

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)


