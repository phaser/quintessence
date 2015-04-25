cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "gtest-entrypoint")
PROJECT (${PROJ_NAME})

library(${PROJ_NAME}
        DEPENDENCY gtest 1.6.0)
