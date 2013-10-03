cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "gtest")
PROJECT (${PROJ_NAME})
mark_lib_for_reuse(${PROJ_NAME})

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
if (QT5)
    SET (SAVE_PLAF ${PLATFORM})
    SET (PLATFORM "osx")
    export_library(${PROJ_NAME})
    SET (PLATFORM "${SAVE_PLAF}")
elseif (IOS OR ANDROID OR OSX)
    make_library(${PROJ_NAME})
else ()
    export_library(${PROJ_NAME})
endif ()

if (LINUX)
    SET(EXPORTED_${PROJ_NAME}_LIB "${EXPORTED_${PROJ_NAME}_LIB} pthread" CACHE INTERNAL "Libraries for ${PROJ_NAME}" FORCE)
endif (LINUX)

