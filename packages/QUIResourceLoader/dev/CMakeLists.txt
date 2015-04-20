# This file is part of QUIReflection.
#
#    QUIReflection is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    QUIReflection is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with QUIReflection.  If not, see <http:#www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIResourceLoader")
PROJECT (${PROJ_NAME})

#IF (DEFINED TESTS)
#    add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
#ENDIF (DEFINED TESTS)

library(${PROJ_NAME}
        DEPENDENCY "QUIUtils" "dev"
        DEPENDENCY "QUIVirtualFS" "dev"
        DEPENDENCY "QUIRenderer" "dev"
        DEPENDENCY "QUIReflection" "dev"
        DEPENDENCY "QUIText" "dev"
        DEPENDENCY "glm"    "0.9.6.3"
)

