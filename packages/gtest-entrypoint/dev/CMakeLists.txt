cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "gtest-entrypoint")
PROJECT (${PROJ_NAME})
mark_lib_for_reuse(${PROJ_NAME})

add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
make_library(${PROJ_NAME})
link_module_dependencies(${PROJ_NAME})
