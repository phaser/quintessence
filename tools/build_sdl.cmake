cmake_minimum_required (VERSION 3.0)

file (DOWNLOAD "https://www.libsdl.org/release/SDL2-2.0.3.zip" "${CMAKE_SOURCE_DIR}/SDL-2.0.3.zip")
exec_program("${CMAKE_COMMAND}" ARGS -E tar -xvf "${CMAKE_SOURCE_DIR}/SDL-2.0.3.zip")
