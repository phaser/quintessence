cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIOpenGLES")
PROJECT (${PROJ_NAME})


include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

IF (WIN32)
    export_library(${PROJ_NAME})
ELSE (WIN32)
	if (ANDROID)
	    LIST (APPEND ${PROJ_NAME}_LIBS "GLESv2")
    endif (ANDROID)

    if (LINUX)
	    LIST (APPEND ${PROJ_NAME}_LIBS "GL")
    endif (LINUX)

    SET(EXPORTED_${PROJ_NAME}_LIB ${${PROJ_NAME}_LIBS} CACHE INTERNAL ${PROJ_NAME} FORCE)
ENDIF (WIN32)


