# This file is part of QUIUtils.
#
#    QUIUtils is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    QUIUtils is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with QUIUtils.  If not, see <http:#www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIUtils")
PROJECT (${PROJ_NAME})


IF (DEFINED TESTS)
    set (ADD_TESTS "DEPENDENCY gtest 1.6.0")
ENDIF (DEFINED TESTS)

library(${PROJ_NAME}
        ${ADD_TESTS}
)

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

IF (LINUX)
    target_link_libraries(${PROJ_NAME} "rt")
ENDIF (LINUX)

IF (ANDROID)
    target_link_libraries(${PROJ_NAME} "log")
ENDIF(ANDROID)
