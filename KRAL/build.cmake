# The project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
#
# klar
# Copyright (C) 2011 Cristian Bidea

cmake_minimum_required (VERSION 2.8)

function(add_target TNAME)
    set (value 0)
    while (value LESS ${ARGC})
        message ("E${value}: ${ARGV${value}}")
        if      ("KRAL_PATH" STREQUAL "${ARGV${value}}")
            math (EXPR value "${value} + 1")
            message ("KRAL_PATH: ${ARGV${value}}")
        elseif  ("PACKAGE_DIRS" STREQUAL "${ARGV${value}}")
            math (EXPR value "${value} + 1")
            message ("PACKAGE_DIRS: ${ARGV${value}}")
        elseif  ("PROJECTS_ROOT" STREQUAL "${ARGV${value}}")
            math (EXPR value "${value} + 1")
            message ("PROJECTS_ROOT: ${ARGV${value}}")
        endif()
        math(EXPR value "${value} + 1")
    endwhile()
endfunction()

include (${CMAKE_SOURCE_DIR}/config_new.cmake)
