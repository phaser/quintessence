cmake_minimum_required (VERSION 2.8)
include (KRAL/config.cmake)

set (KRAL_PATH      "${CMAKE_CURRENT_LIST_DIR}/KRAL/")
set (PACKAGE_DIRS   "${CMAKE_CURRENT_LIST_DIR}/packages;${CMAKE_CURRENT_LIST_DIR}/thirdparty")
set (PROJECTS_ROOT_DIR  "${CMAKE_CURRENT_LIST_DIR}/projects")

# Default target
set (PLATFORM_DEFAULT           "linux")
set (PROJECT_TYPE_DEFAULT       "Unix Makefiles")

# === TARGET
set (CTARGET "SDLDemo-qt")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "qt5")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Unix Makefiles")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\"")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTARGETSDK=MacOSX10.8.sdk ")
set (BUILD_TYPE_${CTARGET}      "debug")

# === TARGET
set (CTARGET "SDLDemo-osx")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "osx")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Xcode")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DRUNTIME_DIR=debug")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\"")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTARGETSDK=MacOSX10.9.sdk ")
#set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTESTS=True ")
set (BUILD_TYPE_${CTARGET}      "debug")

# === TARGET
set (CTARGET "SDLDemo-web")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "web")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Unix Makefiles")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_PD_${CTARGET}  "-DCMAKE_TOOLCHAIN_FILE=${KRAL_PATH}/Emscripten.cmake")
set (BUILD_TYPE_${CTARGET}      "debug")

# === TARGET
set (CTARGET "SDLDemo-osx-lib")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "osx")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Xcode")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DRUNTIME_DIR=debug")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\"")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTARGETSDK=MacOSX10.8.sdk ")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DSHARED_LIB=1 ")
#set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTESTS=True ")
set (BUILD_TYPE_${CTARGET}      "debug")

# === TARGET
set (CTARGET "editor-osx")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "osx")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/editor")
set (BUILD_DIR_${CTARGET}       "editor")
set (PROJECT_TYPE_${CTARGET}    "Xcode")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DRUNTIME_DIR=debug")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs\"")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTARGETSDK=MacOSX10.8.sdk ")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DQT5=1 ")
#set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTESTS=True ")
set (BUILD_TYPE_${CTARGET}      "debug")
set (GENERATE_CMAKELISTS_${CTARGET} True)

# == TARGET
set (CTARGET "SDLDemo-iossim")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "ios")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Xcode")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DIOS_SDK_PATH=\"/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs\"")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DTARGETSDK=iPhoneSimulator7.0.sdk ")
set (BUILD_TYPE_${CTARGET}      "debug")

# == TARGET
set (CTARGET "SDLDemo-android")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "android")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Unix Makefiles")
set (CMAKE_BUILD_OPTIONS_${CTARGET} " -- -j")
set (API_LEVEL_${CTARGET} "android-14")
set (CPU_TARGET_${CTARGET} "armeabi")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DANDROID_APP_NAME=\"SDLDemo\" ")
set (CUSTOM_ARGS_${CTARGET}     "${CUSTOM_ARGS_${CTARGET}} -DANDROID_APP_PACKAGE=\"ro.qui.apps\"")
set (BUILD_TYPE_${CTARGET}      "debug")

# === TARGET
set (CTARGET "SDLDemo-win32")
list (APPEND TARGETS ${CTARGET})
copy_target ("DEFAULT" ${CTARGET})
set (TARGET_NAME_${CTARGET}     "${CTARGET}")
set (PLATFORM_${CTARGET}        "win32")
set (PROJECT_DIR_${CTARGET}     "${CMAKE_CURRENT_LIST_DIR}/SDLDemo")
set (BUILD_DIR_${CTARGET}       "SDLDemo")
set (PROJECT_TYPE_${CTARGET}    "Visual Studio 11")
set (CUSTOM_ARGS_${CTARGET}     "-Wdev -DRUNTIME_SUFFIX=/Debug/SDLDemo.app ")
set (BUILD_TYPE_${CTARGET}      "debug")

