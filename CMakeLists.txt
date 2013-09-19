cmake_minimum_required (VERSION 2.8)
include (./config.cmake)

macro (print_target THE_TARGET)
    set (TARGET_INFO_${THE_TARGET}
        "Platform:\t\t${PLATFORM_${THE_TARGET}}"
        "Project generator:\t\t${PROJECT_TYPE_${THE_TARGET}}"
        "Project directory:\t\t${PROJECT_DIR_${THE_TARGET}}"
        "Build directory:\t\t${BUILD_DIR_${THE_TARGET}}"
        "Custom args:\t\t${CUSTOM_ARGS_${THE_TARGET}}"
        )
endmacro ()

if ("${T}" STREQUAL "")
    set (MSG "${CMAKE_COMMAND} -DT=[target] ."
             "Targets:")
    foreach (target ${TARGETS})
        print_target(${target})
        set (MSG "${MSG}"
                 "${TARGET_INFO_${target}}")
    endforeach ()     
    message (FATAL_ERROR ${MSG})
endif ()


