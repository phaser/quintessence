# The project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/docs/gpl-3.0.txt for more details.
#
# KRAL
# Copyright (C) 2011 Cristian Bidea

if (TESTS)
    ENABLE_TESTING()
endif (TESTS)

# macro taken from this StackOverflow answer 
# http://stackoverflow.com/questions/10113017/setting-the-msvc-runtime-in-cmake
macro(configure_msvc_runtime)
  if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()
    # set compiler options.
    set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    if(${MSVC_RUNTIME} STREQUAL "static")
      message(STATUS
        "MSVC -> forcing use of statically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
      endforeach()
    else()
      message(STATUS
        "MSVC -> forcing use of dynamically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()
      endforeach()
    endif()
  endif()
endmacro()

set (STOP_ON_ERRORS "-Werror=comment")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=return-type")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=uninitialized")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=address")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=sign-compare")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=float-equal")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=strict-overflow")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=switch")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=switch-default")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=reorder")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=init-self")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=missing-include-dirs")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=return-type")
set (STOP_ON_ERRORS "${STOP_ON_ERRORS} -Werror=trigraphs")

if (IOS)
	set (STOP_ON_ERRORS "")
endif (IOS)

#set(BUILD_SHARED_LIBS ON)

set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")

#Build configuration
if (NOT DEFINED CMAKE_BUILD_TYPE)
    message (STATUS "CMAKE_BUILD_TYPE is not defined, defaulting to debug.")
    set(CMAKE_BUILD_TYPE "debug")
    set(CMAKE_CONFIGURATION_TYPES Debug)
else (NOT DEFINED CMAKE_BUILD_TYPE)
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set(CMAKE_CONFIGURATION_TYPES Release)
    else ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set(CMAKE_CONFIGURATION_TYPES Debug)
    endif ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
endif (NOT DEFINED CMAKE_BUILD_TYPE)

#packages
if (NOT DEFINED PACKAGES)
    FILE(TO_CMAKE_PATH "${KRAL_PATH}/../packages" PTMP)
    set (PACKAGES ${PTMP})
    message(STATUS "PACKAGES: ${PACKAGES}")
else (NOT DEFINED PACKAGES)
    LIST (LENGTH LSTTMP LN)
    if (${LN} EQUAL 0)
        foreach(package ${PACKAGES})
            FILE(TO_CMAKE_PATH "${KRAL_PATH}/${package}" package)
            LIST(APPEND LSTTMP ${package})
        endforeach(package)
        set(PACKAGES ${LSTTMP})
        message(STATUS "PACKAGES: ${PACKAGES}")
    endif (${LN} EQUAL 0)
endif (NOT DEFINED PACKAGES)

if (NOT PLATFORM STREQUAL "")
    string (TOUPPER ${PLATFORM} TMPPLATFORM)
    set (${TMPPLATFORM} "ON" CACHE INTERNAL "We are compiling for ${TMPPLATFORM}." FORCE)
endif (NOT PLATFORM STREQUAL "")

set (GNU_GPROF_FLAGS "")
if (DEFINED ENABLE_GPROF_PROFILING)
    message (STATUS "Profiling enabled. ENABLE_GPROF_PROFILING=${ENABLE_GPROF_PROFILING}")
    set (GNU_GPROF_FLAGS "-pg")
endif (DEFINED ENABLE_GPROF_PROFILING)

set (GNU_CXX_FLAGS_DEBUG "${GNU_GPROF_FLAGS} ${CUSTOM_COMPILER_OPTS} -g -O0 -W -Wall -DBUILD_TYPE_DEBUG -DPLATFORM_${TMPPLATFORM}")
set (GNU_C_FLAGS_DEBUG "${GNU_GPROF_FLAGS} ${CUSTOM_COMPILER_OPTS} -g -O0 -W -Wall -DBUILD_TYPE_DEBUG -DPLATFORM_${TMPPLATFORM}")
set (GNU_CXX_FLAGS_RELEASE "-O3 ${CUSTOM_COMPILER_OPTS} -DPLATFORM_${TMPPLATFORM}")
set (GNU_C_FLAGS_RELEASE "-O3 ${CUSTOM_COMPILER_OPTS} -DPLATFORM_${TMPPLATFORM}")

if (ANDROID)
	if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	        set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_DEBUG} -std=gnu++0x -DREX_ANDROID -DHONEYCOMB")
        	set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_DEBUG} -DREX_ANDROID -DHONEYCOMB -std=c99")
	        set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_RELEASE} -std=gnu++0x -DREX_ANDROID -DHONEYCOMB")
        	set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_RELEASE} -DREX_ANDROID -DHONEYCOMB -std=c99")
	endif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) 
elseif (LINUX)
   	if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
		set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_DEBUG} -std=gnu++0x -DREX_GLX")
       	set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_DEBUG} -DREX_GLX")
		set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_RELEASE} -std=gnu++0x -DREX_GLX")
       	set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_RELEASE} -DREX_GLX")
	endif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) 
elseif (WIN32)
        configure_msvc_runtime()	
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D PLATFORM_WIN32 /EHsc /D _VARIADIC_MAX=10 ${CUSTOM_COMPILER_OPTS} ")
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D PLATFORM_WIN32 ${CUSTOM_COMPILER_OPTS} ")
elseif (IOS)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_DEBUG} -std=c++11")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_DEBUG}")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_RELEASE} -std=c++11")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_RELEASE}")

    set (CMAKE_OSX_SYSROOT "${IOS_SDK_PATH}/${TARGETSDK}")
    set (CMAKE_OSX_ARCHITECTURES_DEBUG "${ARCHS_STANDARD_32_BIT}")
    set (CMAKE_OSX_ARCHITECTURES_RELEASE "${ARCHS_STANDARD_32_BIT}")
elseif (OSX)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_DEBUG} -std=c++11")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_DEBUG}")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_RELEASE} -std=c++11")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_RELEASE}")

    set (CMAKE_OSX_SYSROOT "${IOS_SDK_PATH}/${TARGETSDK}")
else()
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_DEBUG} -std=c++11")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_DEBUG}")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${GNU_CXX_FLAGS_RELEASE} -std=c++11")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${GNU_C_FLAGS_RELEASE}")
endif ()

set (DEBUG_MESSAGES "OFF" CACHE INTERNAL "Enable or disable debug messages" FORCE)
