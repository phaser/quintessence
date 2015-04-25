# Copyright (C) 2011-2015 Cristian Bidea
# 
# This project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
cmake_minimum_required (VERSION 3.0)

set (PROJ_NAME "QUIVirtualFS-tests")
project (${PROJ_NAME})

module(${PROJ_NAME}
       DEPENDENCY gtest-entrypoint dev
       DEPENDENCY gtest 1.6.0
       DEPENDENCY QUIUtils dev
       DEPENDENCY QUIVirtualFS dev
)

