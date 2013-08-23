cmake_minimum_required (VERSION 2.8)
set (PROJ_NAME "SDL2")
project (${PROJ_NAME})

include_ios_framework(SDL2 "${CMAKE_CURRENT_LIST_DIR}")
export_ios_framework(${PROJ_NAME} SDL2 "${CMAKE_CURRENT_LIST_DIR}")
