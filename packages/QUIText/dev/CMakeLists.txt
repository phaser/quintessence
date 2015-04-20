cmake_minimum_required (VERSION 2.8)

SET (PROJ_NAME "QUIText")
PROJECT (${PROJ_NAME})

#if (TESTS)
#    add_module_dependency(${PROJ_NAME} "gtest" "1.6.0")
#endif() 

library(${PROJ_NAME}
        DEPENDENCY "lodepng" "20120729"
        DEPENDENCY "glm" "0.9.6.3"
        DEPENDENCY "QUIUtils" "dev"
        DEPENDENCY "SDL2" "2.0.0"
        DEPENDENCY "QUIOpenGLES" "dev"
        DEPENDENCY "QUIVirtualFS" "dev"
        DEPENDENCY "QUI2D" "dev"
        DEPENDENCY "QUIRenderer" "dev"
)
IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	SET_TARGET_PROPERTIES (${PROJ_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)


