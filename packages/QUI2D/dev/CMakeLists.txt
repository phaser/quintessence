# This file is part of QUI2D.
#
#    QUI2D is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published 
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    QUI2D is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with QUI2D.  If not, see <http://www.gnu.org/licenses/>.
cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUI2D")
PROJECT (${PROJ_NAME})

add_module_dependency(${PROJ_NAME} "QUIUtils"      "dev")
add_module_dependency(${PROJ_NAME} "QUIVirtualFS"  "dev")
add_module_dependency(${PROJ_NAME} "QUIRenderer"   "dev")
add_module_dependency(${PROJ_NAME} "QUIOpenGLES"   "dev")
add_module_dependency(${PROJ_NAME} "QUIGameEntry"  "dev")
add_module_dependency(${PROJ_NAME} "glm"           "0.9.3.3")

make_library(${PROJ_NAME})

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC -Werror")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

link_module_dependencies(${PROJ_NAME})

