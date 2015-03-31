#
# Toolchain for cross-compiling to JS using Emscripten
#
# Modify EMSCRIPTEN_PREFIX to your liking. You have to add modules/ directory
# to CMAKE_MODULE_PATH before using the toolchain file so Emscripten platform
# file can be found, e.g.:
#
#  mkdir build-emscripten && cd build-emscripten
#  cmake .. \
#       -DCMAKE_MODULE_PATH=/absolute/path/to/toolchains/modules \
#       -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Emscripten.cmake
#

set(CMAKE_SYSTEM_NAME cppcheck)

# Spoonfeed CMakeFindBinUtils.cmake, as explicitly set CMAKE_AR/CMAKE_RANLIB
# would get overwritten with empty string
#set(_CMAKE_TOOLCHAIN_PREFIX cppcheck)
#set(_CMAKE_TOOLCHAIN_LOCATION ${EMSCRIPTEN_PREFIX})

set(CPPCHECK_TOOLCHAIN_PATH "/opt/local/bin")
set(CMAKE_C_COMPILER "cppcheck")
set(CMAKE_CXX_COMPILER "cppcheck")
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH}
    "${EMSCRIPTEN_TOOLCHAIN_PATH}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
