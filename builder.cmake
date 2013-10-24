cmake_minimum_required (VERSION 2.8)
include (./config.cmake)

macro (print_target THE_TARGET)
    message ("
== ${TARGET_NAME_${THE_TARGET}}
    Platform:\t\t\t${PLATFORM_${THE_TARGET}}
    Project generator:\t${PROJECT_TYPE_${THE_TARGET}}
    Project directory:\t${PROJECT_DIR_${THE_TARGET}}
    Build directory:\t\t${BUILD_DIR_${THE_TARGET}}
    Custom args:\t\t${CUSTOM_ARGS_${THE_TARGET}}")
endmacro ()

if ("${T}" STREQUAL "")
    set (counter "0")
    set (MSG "USAGE: cmake -DT=[target] -D[BUILD_OPTION]=1 -P build.cmake
BUILD_OPTION = GENERATE | COMPILE | UPDATE | BUILD | LIST
target = one of the target listed below
Available targets:")
    foreach (target ${TARGETS})
        math (EXPR counter "${counter} + 1")
        set (TARGET_INFO_${target} "${counter}. [${PLATFORM_${target}}]    ${TARGET_NAME_${target}}")
        set (MSG "${MSG}
    ${TARGET_INFO_${target}}")
    endforeach ()     
    message (FATAL_ERROR ${MSG})
endif ()

set (CMAKE_GENERATED_COMMAND "\"${CMAKE_COMMAND}\" ${CUSTOM_ARGS_${T}} -DPACKAGES=\"${PACKAGE_DIRS}\" -DCMAKE_BUILD_TYPE=Debug -DKRAL_PATH=\"${KRAL_PATH}\" -DPLATFORM=\"${PLATFORM_${T}}\" -G \"${PROJECT_TYPE_${T}}\" \"${PROJECT_DIR_${T}}\" -DCUSTOM_COMPILER_OPTS=\"\"")

if ("${PLATFORM_${T}}" STREQUAL "android")
    # Determine android target number
    set (ANDROID_BINARY "android")
    exec_program("${ANDROID_BINARY} list targets" OUTPUT_VARIABLE ALT_OUTPUT RETURN_VALUE ALTRV)
    if (NOT "${ALTRV}" STREQUAL "0")
        message(STATUS "${ALT_OUTPUT}")
        message(FATAL "android list targets returned error code ${ALTRV}")
    endif()
    string(REGEX MATCH "id: (.*) or.*${API_LEVEL_${T}}" ALT_MATCH ${ALT_OUTPUT})
    set(ANDROID_TARGET "${CMAKE_MATCH_1}")
endif()

if (GENERATE)
    file(REMOVE_RECURSE "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
    file(MAKE_DIRECTORY "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
 
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} ${CMAKE_GENERATED_COMMAND})
elseif (UPDATE)
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" ${CUSTOM_ARGS_${T}} -DPACKAGES=\"${PACKAGE_DIRS}\" -DCMAKE_BUILD_TYPE=Debug -DKRAL_PATH=\"${KRAL_PATH}\" -DPLATFORM=\"${PLATFORM_${T}}\" -G \"${PROJECT_TYPE_${T}}\" \"${PROJECT_DIR_${T}}\" -DCUSTOM_COMPILER_OPTS=\"\")
elseif (COMPILE)
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" --build .)
elseif (LIST)
    print_target(${T})
elseif (BUILD)
    file(REMOVE_RECURSE "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
    file(MAKE_DIRECTORY "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
 
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} ${CMAKE_GENERATED_COMMAND})
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" --build .)
endif()


