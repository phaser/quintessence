cmake_minimum_required (VERSION 2.8)
include (./config.cmake)

macro (print_target THE_TARGET)
    set (TARGET_INFO_${THE_TARGET} "
== ${TARGET_NAME_${THE_TARGET}}
    Platform:\t\t\t${PLATFORM_${THE_TARGET}}
    Project generator:\t${PROJECT_TYPE_${THE_TARGET}}
    Project directory:\t${PROJECT_DIR_${THE_TARGET}}
    Build directory:\t\t${BUILD_DIR_${THE_TARGET}}
    Custom args:\t\t${CUSTOM_ARGS_${THE_TARGET}}")
endmacro ()

message (STATUS "TARGET: ${T}")
if ("${T}" STREQUAL "")
    set (MSG "USAGE: ${CMAKE_COMMAND} -P build.cmake -DT=[target]
Available targets:")
    foreach (target ${TARGETS})
        print_target(${target})
        set (MSG "${MSG}"
                 "${TARGET_INFO_${target}}")
    endforeach ()     
    message (FATAL_ERROR ${MSG})
endif ()

if (GENERATE)
    file(REMOVE_RECURSE "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
    file(MAKE_DIRECTORY "${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}}")
    message (STATUS "${CMAKE_COMMAND} ${CUSTOM_ARGS_${T}} -DPACKAGES=\"${PACKAGE_DIRS}\" -DCMAKE_BUILD_TYPE=Debug -DKRAL_PATH=\"${KRAL_PATH}\" -DPLATFORM=\"${PLATFORM_${T}}\" -G \"${PROJECT_TYPE_${T}}\" \"${PROJECT_DIR_${T}}\" -DCUSTOM_COMPILER_OPTS=\"\"")
 
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" ${CUSTOM_ARGS_${T}} -DPACKAGES=\"${PACKAGE_DIRS}\" -DCMAKE_BUILD_TYPE=Debug -DKRAL_PATH=\"${KRAL_PATH}\" -DPLATFORM=\"${PLATFORM_${T}}\" -G \"${PROJECT_TYPE_${T}}\" \"${PROJECT_DIR_${T}}\" -DCUSTOM_COMPILER_OPTS=\"\")
elseif (UPDATE)
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" ${CUSTOM_ARGS_${T}} -DPACKAGES=\"${PACKAGE_DIRS}\" -DCMAKE_BUILD_TYPE=Debug -DKRAL_PATH=\"${KRAL_PATH}\" -DPLATFORM=\"${PLATFORM_${T}}\" -G \"${PROJECT_TYPE_${T}}\" \"${PROJECT_DIR_${T}}\" -DCUSTOM_COMPILER_OPTS=\"\")
elseif (COMPILE)
    exec_program ("${CMAKE_COMMAND}" ARGS -E chdir ${PROJECTS_ROOT_DIR}/${BUILD_DIR_${T}} 
            \"${CMAKE_COMMAND}\" --build .)
endif()


