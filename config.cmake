cmake_minimum_required (VERSION 2.8)
include (KRAL/config.cmake)

set (KRAL_PATH      "${CMAKE_CURRENT_LIST_DIR}/KRAL/")
set (PACKAGE_DIRS   "../packages;..thirdparty")
set (PROJECTS_ROOT_DIR  "${CMAKE_CURRENT_LIST_DIR}/projects")

# Default target
set (PLATFORM_DEFAULT           "linux")
set (PROJECT_TYPE_DEFAULT       "Unix Makefiles")

set (CTARGET "SDLDemo-osx")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "osx")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Xcode")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev -DRUNTIME_SUFFIX=/Debug ")

set (CTARGET "SDLDemo-win32")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "win32")
set (PROJECT_DIR_${CTARGET}     "SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Visual Studio 11 Win64")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev -DRUNTIME_SUFFIX=/Debug/SDLDemo.app ")
