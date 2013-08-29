cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "oolua")
project (${PROJ_NAME})

add_module_dependency(${PROJ_NAME} "lua" "5.2.2")

if (TESTS)
    add_module_dependency(${PROJ_NAME}Tests "gtest-entrypoint" "dev")
    add_module_dependency(${PROJ_NAME}Tests "gtest" "1.6.0")
endif ()

make_library(${PROJ_NAME})

link_module_dependencies(${PROJ_NAME})

if (TESTS)
    link_module_dependencies(${PROJ_NAME}Tests)
endif()

