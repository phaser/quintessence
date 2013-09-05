cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIMemoryUtils")
PROJECT (${PROJ_NAME})


IF (DEFINED TESTS)
    add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
ENDIF (DEFINED TESTS)

add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")

make_library(${PROJ_NAME})

link_module_dependencies(${PROJ_NAME})
