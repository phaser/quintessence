# This file is part of QUIRenderer.
#
#    QUIRenderer is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    QUIRenderer is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with QUIRenderer.  If not, see <http:#www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIRenderer")
PROJECT (${PROJ_NAME})

library(${PROJ_NAME}
        DEPENDENCY "QUIUtils"       "dev"
        DEPENDENCY "OpenGLES"    "dev"
        DEPENDENCY "QUIVirtualFS"   "dev"
        DEPENDENCY "QUIImage"       "dev"
        DEPENDENCY "tinyxml"        "2.6.2" 
        DEPENDENCY "glm"            "0.9.6.3"
)

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

