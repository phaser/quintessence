# The project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
#
# KRAL
# Copyright (C) 2011 Cristian Bidea

cmake_minimum_required (VERSION 2.8)

INCLUDE (KRALConfig)

set (SOURCES_EXTENSIONS "*.c;*.cc;*.cpp;*.cxx;*.m;*.mm;*.ui")
set (INCLUDE_EXTENSIONS "*.h;*.hpp")

MACRO (set_global_target_property property value)
    SET(GLOBAL_TARGET_PROPERTY "${GLOBAL_TARGET_PROPERTY};${property}[]${value}" CACHE INTERNAL "Global target properties" FORCE)
ENDMACRO (set_global_target_property)

MACRO (apply_global_target_properties target)
    foreach (property ${GLOBAL_TARGET_PROPERTY}) 
        if (NOT "${property}" STREQUAL "") 
            string(REPLACE "[]" ";" pvpair "${property}")
            list(GET pvpair 0 property_name)
            list(GET pvpair 1 property_value)
            set_target_properties(${target} PROPERTIES ${property_name} ${property_value}) 
        endif (NOT "${property}" STREQUAL "")
    endforeach (property)
ENDMACRO (apply_global_target_properties)

MACRO (generate_ndkgdb_config TARGET)    
    MESSAGE(STATUS "Generating ndk-gdb config...")
    MESSAGE(STATUS "ANDROID_ABI: ${ANDROID_ABI}")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/obj")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/obj/local")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/obj/local/${ANDROID_ABI}")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/libs")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/libs/${ANDROID_ABI}")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/libs/armeabi")
    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_BINARY_DIR}/android/jni")
    FILE (WRITE "${CMAKE_BINARY_DIR}/android/jni/Android.mk" "")

    SET (GDBSETUPFILE "${CMAKE_BINARY_DIR}/android/libs/${ANDROID_ABI}/gdb.setup")
    FILE (WRITE "${GDBSETUPFILE}" "set solib-search-path ${CMAKE_BINARY_DIR}/android/obj/local/${ANDROID_ABI}\n")
    FILE (APPEND "${GDBSETUPFILE}" "directory $ENV{NDK}/platforms/${ANDROID_API_LEVEL}/arch-arm/usr/include ${SOURCE_LOCATIONS}\n")

    EXEC_PROGRAM("\"${CMAKE_COMMAND}\" -E copy $ENV{NDK}/prebuilt/android-arm/gdbserver/gdbserver ${CMAKE_BINARY_DIR}/android/libs/armeabi")
    
    ADD_CUSTOM_COMMAND(TARGET ${TARGET}
                       POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" ARGS "-E" "copy_directory" "${CMAKE_CURRENT_LIST_DIR}/libs" "${CMAKE_BINARY_DIR}/android/obj/local"
                       COMMAND "${CMAKE_COMMAND}" ARGS "-E" "copy_directory" "${CMAKE_BINARY_DIR}/android/libs" "${CMAKE_BINARY_DIR}/android/obj/local")
ENDMACRO (generate_ndkgdb_config)

MACRO(generate_android_project)
    SET (ANDROID_APP_NAME ${ARGV0})
    SET (ANDROID_APP_PACKAGE ${ARGV1})
    SET (ANDROID_BINARY ${ARGV2})
	EXEC_PROGRAM ("\"${CMAKE_COMMAND}\" -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/../${PLATFORM}")
    EXEC_PROGRAM ("${ANDROID_BINARY} create project --target ${ANDROID_TARGET} --name ${ANDROID_APP_NAME} --path ${CMAKE_BINARY_DIR}/${PLATFORM} --activity ${ANDROID_APP_NAME}Activity --package ${ANDROID_APP_PACKAGE}")
ENDMACRO(generate_android_project)

# Returns TRUE or FALSe in var if the list
# contains the value
MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_CONTAINS)

MACRO(COPY_RUNTIME_FILES)
	if (NOT "${ARGV0}" STREQUAL "")
		SET (DIR_TO_COPY "${CMAKE_CURRENT_LIST_DIR}${ARGV0}")
		IF (NOT "${RUNTIME_DIR}" STREQUAL "")
			if (EXISTS "${DIR_TO_COPY}/")
				EXEC_PROGRAM ("\"${CMAKE_COMMAND}\" -E copy_directory \"${DIR_TO_COPY}\" \"${RUNTIME_DIR}${RUNTIME_SUFFIX}\"")
			endif ()
		ENDIF (NOT "${RUNTIME_DIR}" STREQUAL "")
	else ()
		IF (NOT "${RUNTIME_DIR}" STREQUAL "")
			if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/runtime/")
				EXEC_PROGRAM ("\"${CMAKE_COMMAND}\" -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}/runtime/common\" \"${RUNTIME_DIR}${RUNTIME_SUFFIX}\"")
				EXEC_PROGRAM ("\"${CMAKE_COMMAND}\" -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}/runtime/${PLATFORM}\" \"${RUNTIME_DIR}${RUNTIME_SUFFIX}\"") 
			endif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/runtime/")
		ENDIF (NOT "${RUNTIME_DIR}" STREQUAL "")
	endif ()
ENDMACRO(COPY_RUNTIME_FILES)

MACRO(CLEAR_CACHE)
    SET (SOURCE_LOCATIONS "" CACHE INTERNAL "sources locations" FORCE)
    SET (KRAL_MODULES_ADDED "" CACHE INTERNAL "Modules used by this project" FORCE)
    SET (GLOBAL_TARGET_PROPERTY "" CACHE INTERNAL "Global target properties" FORCE)
ENDMACRO(CLEAR_CACHE)

# List files from include, source/common and source/${PLATFORM}
# The list is later used to create libraries and/or executables
macro(list_files NAME)
	IF (DEBUG_MESSAGES)
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/include")
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/source/common")
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}")
	ENDIF (DEBUG_MESSAGES)

        SET (SOURCE_LOCATIONS "${SOURCE_LOCATIONS} ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/source/common ${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}" CACHE INTERNAL "sources locations" FORCE)

    foreach (EXTENSION ${INCLUDE_EXTENSIONS}) 
        file (GLOB_RECURSE F_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/${EXTENSION}")
	    list (APPEND ${NAME}_F_INCLUDE ${F_INCLUDE})
    endforeach (EXTENSION)

    foreach (EXTENSION ${SOURCES_EXTENSIONS})
        FILE (GLOB_RECURSE F_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/common/${EXTENSION}")
	    LIST (APPEND ${NAME}_F_SOURCES ${F_SOURCES})
        FILE (GLOB_RECURSE plaf_F_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}/${EXTENSION}")
	    LIST (APPEND ${NAME}_plaf_F_SOURCES ${plaf_F_SOURCES})
    endforeach (EXTENSION)
    
    IF (IOS)
        FILE (GLOB_RECURSE PNG_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}/*.png")
        SET_SOURCE_FILES_PROPERTIES(${PNG_SOURCES}
                                      PROPERTIES
                                      MACOSX_PACKAGE_LOCATION Resources
        )
        LIST (APPEND ${NAME}_plaf_F_SOURCES "${PNG_SOURCES}")

        FILE (GLOB_RECURSE XIB_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}/*.xib")
        SET_SOURCE_FILES_PROPERTIES(${XIB_SOURCES}
                                      PROPERTIES
                                      MACOSX_PACKAGE_LOCATION Resources
        )
        LIST (APPEND ${NAME}_plaf_F_SOURCES "${XIB_SOURCES}")

        FILE (GLOB_RECURSE ZIP_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}/*.zip")
        SET_SOURCE_FILES_PROPERTIES(${ZIP_SOURCES}
                                      PROPERTIES
                                      MACOSX_PACKAGE_LOCATION Resources
        )
        LIST (APPEND ${NAME}_plaf_F_SOURCES "${ZIP_SOURCES}")

        FILE (GLOB_RECURSE OTHER_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/${PLATFORM}/iTunesArtwork")
        SET_SOURCE_FILES_PROPERTIES(${OTHER_SOURCES}
                                      PROPERTIES
                                      MACOSX_PACKAGE_LOCATION Resources
        )
        LIST (APPEND ${NAME}_plaf_F_SOURCES "${OTHER_SOURCES}")
    ENDIF (IOS)

	IF (DEBUG_MESSAGES)
		MESSAGE("SOURCES: ${${NAME}_F_SOURCES}")
		MESSAGE("PLAF SOURCES: ${${NAME}_plaf_F_SOURCES}")
	ENDIF (DEBUG_MESSAGES)

endmacro(list_files)

# make_library is used in packaged modules to add a library
# the macro assumes a standard directory layout with include files
# placed in include and source files placed in source/common for
# independent source files and source/${PLATFORM} for platform
# dependent files.
macro(make_library NAME)
	MESSAGE (STATUS "Creating library ${NAME}")
	IF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include")
		include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
	ENDIF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include")

	IF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")
		include_directories("${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")
	ENDIF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")

    list_files (${NAME})

	add_library (${NAME} ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})
    add_tests(${NAME} ${NAME})

	SET(EXPORTED_${NAME}_LIB ${NAME} CACHE INTERNAL ${NAME} FORCE)
	IF (IOS)
		set_property( TARGET ${NAME} PROPERTY XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.3 )
	ENDIF (IOS)
    apply_global_target_properties(${NAME})
    COPY_RUNTIME_FILES() 
endmacro(make_library)

# declare_target -> used only to expose the include files for a
# package
macro(declare_target NAME)
    include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
endmacro(declare_target)

#make_shared_library
macro(make_shared_library NAME)
	MESSAGE (STATUS "Creating shared library ${NAME}")

	IF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include")
		include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
	ENDIF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include")

	IF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")
		include_directories("${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")
	ENDIF (EXISTS "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}")
	
	list_files (${NAME})

	IF (IOS)
    	add_library (${NAME} MACOSX_BUNDLE SHARED ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})
	ELSE (IOS)
    	add_library (${NAME} SHARED ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})
    ENDIF (IOS)

    add_tests(${NAME} ${NAME})
	SET(EXPORTED_${NAME}_LIB ${NAME} CACHE INTERNAL ${NAME} FORCE)
	IF (IOS)
		set_property( TARGET ${NAME} PROPERTY XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.3 )
	ENDIF (IOS)
    apply_global_target_properties(${NAME})
    COPY_RUNTIME_FILES() 
endmacro(make_shared_library)

# This function it's used by packages that don't have sources, only precompiled libs.
macro(export_library NAME)
	MESSAGE (STATUS "Exporting library ${NAME}")
	include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
    IF (NOT "${ARGV1}" STREQUAL "")
	    export_all_libraries (${NAME} ${ARGV1})
    ELSE (NOT "${ARGV1}" STREQUAL "")
	    export_all_libraries (${NAME})
    ENDIF (NOT "${ARGV1}" STREQUAL "")
	SET(EXPORTED_${NAME}_LIB ${${NAME}_LIBS} CACHE INTERNAL ${NAME} FORCE)
    COPY_RUNTIME_FILES() 
endmacro(export_library)

# This function is used to export all libraries contained in the libs folder
# of the package.
macro(export_all_libraries NAME)
	#todo find a way to abstract the extension of the library
	file (GLOB_RECURSE ${NAME}_LIBS "${CMAKE_CURRENT_LIST_DIR}/lib/${PLATFORM}${ARGV1}/*")

	STRING(REPLACE ";" " " ${NAME}_LIBS "${${NAME}_LIBS}")
	SET(EXPORTED_${NAME}_LIB ${${NAME}_LIBS} CACHE INTERNAL ${NAME} FORCE)
    MESSAGE(STATUS "---> Libraries exported: ${EXPORTED_${NAME}_LIB}")
endmacro(export_all_libraries)

macro(android_build_project_post_build NAME)
	if (ANDROID)
       IF (CMAKE_BUILD_TYPE STREQUAL "release")
            # for the release version we also sign the application
            ADD_CUSTOM_COMMAND (TARGET ${NAME}
                    POST_BUILD
                    COMMAND rm ARGS -rf ${CMAKE_BINARY_DIR}/${PLATFORM}/bin/*
                    COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory ${LIB_DIR} ${CMAKE_BINARY_DIR}/${PLATFORM}/libs
                    COMMAND ${CMAKE_COMMAND} ARGS -E chdir ${CMAKE_BINARY_DIR}/${PLATFORM} ant${CMDEXT} ${CMAKE_BUILD_TYPE}
                ) 
       ELSE (CMAKE_BUILD_TYPE STREQUAL "release")
            ADD_CUSTOM_COMMAND (TARGET ${NAME}
                    POST_BUILD
                    COMMAND rm ARGS -rf ${CMAKE_BINARY_DIR}/${PLATFORM}/bin/*
                    COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory ${LIB_DIR} ${CMAKE_BINARY_DIR}/${PLATFORM}/libs
                    COMMAND ${CMAKE_COMMAND} ARGS -E chdir ${CMAKE_BINARY_DIR}/${PLATFORM} ant${CMDEXT} ${CMAKE_BUILD_TYPE}
                )
        ENDIF (CMAKE_BUILD_TYPE STREQUAL "release")
	endif (ANDROID)
endmacro(android_build_project_post_build)

# build_module builds an entry point module, a module ment to be run. The directory
# layout is the same as in make_library.
# For win32 apps give as the second argument WIN32
# For iPhone MACOSX_BUNDLE
macro(build_module)
    SET (KRAL_MODULES_ADDED "" CACHE INTERNAL "Modules used by this project" FORCE)
    SET (NAME ${ARGV0})
    SET (BUILD_TYPE ${ARGV1})
	MESSAGE (STATUS "Creating module ${NAME}")
	list_files (${NAME})
	include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
	if (ANDROID)
		add_library(${NAME} SHARED ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})
        add_tests(${NAME} ${NAME})
	else (ANDROID)
		add_executable (${NAME} ${BUILD_TYPE} ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})	
		IF(DEFINED TESTS)
		    IF(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests")
		    	add_library(${NAME}_TESTLIB ${${NAME}_F_INCLUDE} ${${NAME}_F_SOURCES} ${${NAME}_plaf_F_SOURCES})
                link_module_dependencies("${NAME}" "_TESTLIB")
                add_tests(${NAME} ${NAME}_TESTLIB)
		    ENDIF(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests")
		ENDIF(DEFINED TESTS)
	endif (ANDROID)
	IF (IOS)
		set_property( TARGET ${NAME} PROPERTY XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.3 )
	ENDIF (IOS)
    COPY_RUNTIME_FILES()
    apply_global_target_properties(${NAME})
    CLEAR_CACHE()
endmacro(build_module)

# add_module_dependency adds a directory and links the target module with the PNAME module.
macro(add_module_dependency PNAME NAME VERSION)
	MESSAGE (STATUS "${PNAME}: Adding module dependency ${NAME} [${VERSION}]")
	SET (PACKAGE_EXISTS False)
	FOREACH (package ${PACKAGES})
    	IF(EXISTS "${package}/${NAME}/${VERSION}")
    	    SET (PACKAGE_EXISTS True)
	    	IF (DEFINED ${DEBUG_MESSAGES})
		    	MESSAGE ("MOD_ADDED_NAME: ${MOD_ADDED_${NAME}}")
		    ENDIF (DEFINED ${DEBUG_MESSAGES})

            LIST_CONTAINS(QRESULT ${NAME} ${KRAL_MODULES_ADDED})
    		IF (NOT QRESULT)
	    		add_subdirectory(${package}/${NAME}/${VERSION} ${CMAKE_BINARY_DIR}/${NAME})
		    	LIST (APPEND KRAL_MODULES_ADDED ${NAME})
		    	SET (KRAL_MODULES_ADDED "${KRAL_MODULES_ADDED}" CACHE INTERNAL "Modules used by this project" FORCE)
    		ENDIF (NOT QRESULT)

	    	IF (EXISTS "${package}/${NAME}/${VERSION}/include")
		    	include_directories("${package}/${NAME}/${VERSION}/include")
		    ENDIF (EXISTS "${package}/${NAME}/${VERSION}/include")

		    IF (EXISTS "${package}/${NAME}/${VERSION}/include/${PLATFORM}")
			    include_directories("${package}/${NAME}/${VERSION}/include/${PLATFORM}")
		    ENDIF (EXISTS "${package}/${NAME}/${VERSION}/include/${PLATFORM}")

		    include_directories("${package}/${NAME}/${VERSION}/include")
            SET(LIBS_${PNAME} "${LIBS_${PNAME}} ${EXPORTED_${NAME}_LIB}" CACHE INTERNAL LIBS_${PNAME} FORCE)
	    ENDIF(EXISTS "${package}/${NAME}/${VERSION}")
	ENDFOREACH (package)
	
	IF (NOT PACKAGE_EXISTS)
        MESSAGE(ERROR ": Package ${NAME} doesn't exist in any package location!!!")
	ENDIF (NOT PACKAGE_EXISTS)
endmacro(add_module_dependency)

macro(use_module_includes PNAME NAME VERSION)
	MESSAGE (STATUS "${PNAME}: Adding module includes ${NAME} [${VERSION}]")
	SET (PACKAGE_EXISTS False)
	FOREACH (package ${PACKAGES})
    	IF(EXISTS "${package}/${NAME}/${VERSION}")
    	    SET (PACKAGE_EXISTS True)
			
	    	IF (EXISTS "${package}/${NAME}/${VERSION}/include")
		    	include_directories("${package}/${NAME}/${VERSION}/include")
		    ENDIF (EXISTS "${package}/${NAME}/${VERSION}/include")

		    IF (EXISTS "${package}/${NAME}/${VERSION}/include/${PLATFORM}")
			    include_directories("${package}/${NAME}/${VERSION}/include/${PLATFORM}")
		    ENDIF (EXISTS "${package}/${NAME}/${VERSION}/include/${PLATFORM}")

		    include_directories("${package}/${NAME}/${VERSION}/include")
	    ENDIF(EXISTS "${package}/${NAME}/${VERSION}")
	ENDFOREACH (package)
	
	IF (NOT PACKAGE_EXISTS)
        MESSAGE(ERROR ": Package ${PNAME} doesn't exist in any package location!!!")
	ENDIF (NOT PACKAGE_EXISTS)
endmacro(use_module_includes )

# link_module_dependencies is called after one adds some dependencies with
# add_module_dependency macro. The add_module_dependency macro configures the
# dependency and then to tell CMake to link the module with all its dependencies
# you call this macro.
macro(link_module_dependencies)
    SET (PNAME ${ARGV0})
    MESSAGE ("LIBS: ${LIBS_${PNAME}}")
    STRING(STRIP ${LIBS_${PNAME}} LIBS_${PNAME})
    STRING(REPLACE " " ";" LIBLIST "${LIBS_${PNAME}}")
    foreach(library ${LIBLIST})
        TARGET_LINK_LIBRARIES(${PNAME} ${library})
        IF (NOT "${ARGV1}" STREQUAL "")
            TARGET_LINK_LIBRARIES("${PNAME}${ARGV1}" ${library})
        ENDIF (NOT "${ARGV1}" STREQUAL "")
    endforeach(library)
endmacro(link_module_dependencies)

# macro to add tests for a particular project
macro(add_tests)
SET (AD_NAME ${ARGV0})
SET (LIB ${ARGV1})
IF(DEFINED TESTS)
IF(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests")
    MESSAGE(STATUS " Adding tests to ${AD_NAME}.")
	IF (DEBUG_MESSAGES)
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/tests/include")
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/tests/source/common")
		MESSAGE("PATH: ${CMAKE_CURRENT_LIST_DIR}/tests/source/${PLATFORM}")
	ENDIF (DEBUG_MESSAGES)

    SET (${AD_NAME}_F_INCLUDE "")
    SET (${AD_NAME}_F_SOURCES "")
   
    foreach (EXTENSION ${INCLUDE_EXTENSIONS}) 
        file (GLOB_RECURSE F_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/tests/include/${EXTENSION}")
	    list (APPEND ${AD_NAME}_F_INCLUDE ${F_INCLUDE})
    endforeach (EXTENSION)

    foreach (EXTENSION ${SOURCES_EXTENSIONS})
        FILE (GLOB_RECURSE F_SOURCES "${CMAKE_CURRENT_LIST_DIR}/tests/source/common/${EXTENSION}")
	    LIST (APPEND ${AD_NAME}_F_SOURCES ${F_SOURCES})
        FILE (GLOB_RECURSE plaf_F_SOURCES "${CMAKE_CURRENT_LIST_DIR}/tests/source/${PLATFORM}/${EXTENSION}")
	    LIST (APPEND ${AD_NAME}_plaf_F_SOURCES ${plaf_F_SOURCES})
    endforeach (EXTENSION)
    
	IF (DEBUG_MESSAGES)
		MESSAGE("SOURCES: ${${AD_NAME}_F_SOURCES}")
		MESSAGE("PLAF SOURCES: ${${AD_NAME}_plaf_F_SOURCES}")
	ENDIF (DEBUG_MESSAGES)

	add_executable (${AD_NAME}Tests ${BUILD_TYPE} ${${AD_NAME}_F_INCLUDE} ${${AD_NAME}_F_SOURCES} ${${AD_NAME}_plaf_F_SOURCES})
    if (IOS)
        link_ios_framework(${AD_NAME}Tests Foundation)
        link_ios_framework(${AD_NAME}Tests OpenGLES)
        link_ios_framework(${AD_NAME}Tests GLKit)
        link_ios_framework(${AD_NAME}Tests UIKit)
    endif (IOS)
    add_test(TEST_${AD_NAME} "${CMAKE_CURRENT_BINARY_DIR}/${AD_NAME}Tests")
	TARGET_LINK_LIBRARIES (${AD_NAME}Tests ${LIB})
ENDIF(EXISTS "${CMAKE_CURRENT_LIST_DIR}/tests")
ENDIF(DEFINED TESTS)
endmacro(add_tests)

# Used to find and link an IOS framework
macro(link_ios_framework)
    SET(LIF_PROJ_NAME ${ARGV0})
    SET(LIF_NAME ${ARGV1})
    FIND_LIBRARY (FRAMEWORK_${LIF_NAME}
                  NAMES ${LIF_NAME}
                  PATHS ${CMAKE_OSX_SYSROOT}/System/Library ${ARGV1}
                  PATH_SUFFIXES Frameworks
                  NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(FRAMEWORK_${LIF_NAME})
    IF (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
        MESSAGE (ERROR ": Framework ${LIF_NAME} not found")
    ELSE (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
        TARGET_LINK_LIBRARIES (${LIF_PROJ_NAME} ${FRAMEWORK_${LIF_NAME}})
        MESSAGE (STATUS "Framework ${LIF_NAME} found at ${FRAMEWORK_${LIF_NAME}}")
    ENDIF (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
endmacro(link_ios_framework)

macro(include_ios_framework)
    SET(NAME ${ARGV0})
    FIND_LIBRARY (FRAMEWORK_${NAME}
                  NAMES ${NAME}
                  PATHS ${CMAKE_OSX_SYSROOT}/System/Library ${ARGV1}
                  PATH_SUFFIXES Frameworks
                  NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(FRAMEWORK_${NAME})
    IF (${FRAMEWORK_${NAME}} STREQUAL FRAMEWORK_${NAME}-NOTFOUND)
        MESSAGE (ERROR ": Framework ${NAME} not found")
    ELSE (${FRAMEWORK_${NAME}} STREQUAL FRAMEWORK_${NAME}-NOTFOUND)
	include_directories("${FRAMEWORK_${NAME}}/Headers")
        MESSAGE (STATUS "Framework ${NAME} found at ${FRAMEWORK_${NAME}} and included.")
    ENDIF (${FRAMEWORK_${NAME}} STREQUAL FRAMEWORK_${NAME}-NOTFOUND)
endmacro(include_ios_framework)

macro(export_ios_framework)
    SET(LIF_PROJ_NAME ${ARGV0})
    SET(LIF_NAME ${ARGV1})
    FIND_LIBRARY (FRAMEWORK_${LIF_NAME}
                  NAMES ${LIF_NAME}
                  PATHS ${CMAKE_OSX_SYSROOT}/System/Library ${ARGV1}
                  PATH_SUFFIXES Frameworks
                  NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(FRAMEWORK_${LIF_NAME})
    IF (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
        MESSAGE (ERROR ": Framework ${LIF_NAME} not found")
    ELSE (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
        SET(EXPORTED_${LIF_PROJ_NAME}_LIB "${FRAMEWORK_${LIF_NAME}}" CACHE INTERNAL ${PROJ_NAME} FORCE)
        MESSAGE (STATUS "Framework ${LIF_NAME} found at ${FRAMEWORK_${LIF_NAME}}")
    ENDIF (${FRAMEWORK_${LIF_NAME}} STREQUAL FRAMEWORK_${LIF_NAME}-NOTFOUND)
endmacro()
