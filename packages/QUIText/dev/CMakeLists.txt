cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIText")
PROJECT (${PROJ_NAME})

add_module_dependency(${PROJ_NAME} "lodepng" "20120729")
add_module_dependency(${PROJ_NAME} "glm" "0.9.3.3")
add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
add_module_dependency(${PROJ_NAME} "QUIUtils" "dev")
add_module_dependency(${PROJ_NAME} "QUIOpenGLES" "dev")
add_module_dependency(${PROJ_NAME} "QUIVirtualFS" "dev")
add_module_dependency(${PROJ_NAME} "QUI2D" "dev")
add_module_dependency(${PROJ_NAME} "QUIRenderer" "dev")

make_library(${PROJ_NAME})

IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

link_module_dependencies(${PROJ_NAME})

