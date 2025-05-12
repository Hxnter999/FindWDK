# Redistribution and use is allowed under the OSI-approved 3-clause BSD license.
# Copyright (c) 2018 Sergey Podobry (sergey.podobry at gmail.com). All rights reserved.

#.rst:
# FindWDK
# ----------
#
# This module searches for the installed Windows Development Kit (WDK) and
# exposes commands for creating kernel drivers and kernel libraries.
#
# Output variables:
# - `WDK_FOUND` -- if false, do not try to use WDK
# - `WDK_ROOT` -- where WDK is installed
# - `WDK_VERSION` -- the version of the selected WDK
# - `WDK_WINVER` -- the WINVER used for kernel drivers and libraries
#       (default value is `0x0601` and can be changed per target or globally)
# - `WDK_NTDDI_VERSION` -- the NTDDI_VERSION used for kernel drivers and libraries,
#       if not set, the value will be automatically calculated by WINVER
#       (default value is left blank and can be changed per target or globally)
# - `FINDWDK_DIR` -- the directory where FindWDK.cmake is located


# Example usage:
#
#   find_package(WDK REQUIRED)
#
#   wdk_add_driver(KmdfCppDriver KMDF 1.15
#       Main.cpp
#   )
#   target_link_libraries(KmdfCppDriver WDK::HAL)
#

if (DEFINED ENV{WDKContentRoot})
    file(GLOB WDK_NTDDK_FILES
            "$ENV{WDKContentRoot}/Include/*/km/ntddk.h" # WDK 10
            "$ENV{WDKContentRoot}/Include/km/ntddk.h" # WDK 8.0, 8.1
    )
else ()
    file(GLOB WDK_NTDDK_FILES
            "C:/Program Files*/Windows Kits/*/Include/*/km/ntddk.h" # WDK 10
            "D:/Program Files*/Windows Kits/*/Include/*/km/ntddk.h" # WDK 10 on D:
            "C:/Program Files*/Windows Kits/*/Include/km/ntddk.h" # WDK 8.0, 8.1
            "D:/Program Files*/Windows Kits/*/Include/km/ntddk.h" # WDK 8.0, 8.1 on D:
    )
endif ()

if (WDK_NTDDK_FILES)
    if (NOT CMAKE_VERSION VERSION_LESS 3.18.0)
        list(SORT WDK_NTDDK_FILES COMPARE NATURAL) # sort to use the latest available WDK
    endif ()

    list(GET WDK_NTDDK_FILES -1 WDK_LATEST_NTDDK_FILE)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WDK REQUIRED_VARS WDK_LATEST_NTDDK_FILE)

if (NOT WDK_LATEST_NTDDK_FILE)
    return()
endif ()

get_filename_component(WDK_ROOT ${WDK_LATEST_NTDDK_FILE} DIRECTORY)
get_filename_component(WDK_ROOT ${WDK_ROOT} DIRECTORY)
get_filename_component(WDK_VERSION ${WDK_ROOT} NAME)
get_filename_component(WDK_ROOT ${WDK_ROOT} DIRECTORY)
if (NOT WDK_ROOT MATCHES ".*/[0-9][0-9.]*$") # WDK 10 has a deeper nesting level
    get_filename_component(WDK_ROOT ${WDK_ROOT} DIRECTORY) # go up once more
    set(WDK_LIB_VERSION "${WDK_VERSION}")
    set(WDK_INC_VERSION "${WDK_VERSION}")
else () # WDK 8.0, 8.1
    set(WDK_INC_VERSION "")

    foreach (VERSION winv6.3 win8 win7)
        if (EXISTS "${WDK_ROOT}/Lib/${VERSION}/")
            set(WDK_LIB_VERSION "${VERSION}")
            break()
        endif ()
    endforeach ()

    set(WDK_VERSION "${WDK_LIB_VERSION}")
endif ()

message(STATUS "WDK_ROOT: " ${WDK_ROOT})
message(STATUS "WDK_VERSION: " ${WDK_VERSION})

foreach (_dir ${CMAKE_MODULE_PATH})
    if (EXISTS "${_dir}/FindWDK.cmake")
        set(FINDWDK_DIR "${_dir}")
        message(STATUS "FINDWDK_DIR found: ${FINDWDK_DIR}")
        break()
    endif ()
endforeach ()

if (NOT DEFINED FINDWDK_DIR)
    message(WARNING "Failed to find FindWDK.cmake in CMAKE_MODULE_PATH! Did you add the correct directory to CMAKE_MODULE_PATH?")
endif ()


set(WDK_WINVER "0x0601" CACHE STRING "Default WINVER for WDK targets")
set(WDK_NTDDI_VERSION "" CACHE STRING "Specified NTDDI_VERSION for WDK targets if needed")

set(WDK_COMPILE_FLAGS
        -ffreestanding
        -fmerge-all-constants
        -fno-rtti
        -fno-exceptions
        -fno-stack-protector
        -fno-stack-check
        -mno-stack-arg-probe
        -mstack-alignment=16

        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wpointer-arith
        -Wstrict-overflow=5
        -Wnull-dereference
        -Wformat=2
        -Wcast-align
        -Wstrict-aliasing=2
)

set(WDK_COMPILE_DEFINITIONS "WINNT=1")
set(WDK_COMPILE_DEFINITIONS_DEBUG "MSC_NOOPT;DEPRECATE_DDK_FUNCTIONS=1;DBG=1")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND WDK_COMPILE_DEFINITIONS "_AMD64_;AMD64;_WIN64")
    set(WDK_PLATFORM "x64")
else ()
    message(FATAL_ERROR "Unsupported architecture")
endif ()

set(WDK_LINK_FLAGS
        -nostdlib
        -nodefaultlibs
        -Wl,-e,DriverEntry
        -Wl,--stack=16384
)


# Generate imported targets for WDK lib files
file(GLOB WDK_LIBRARIES "${WDK_ROOT}/Lib/${WDK_LIB_VERSION}/km/${WDK_PLATFORM}/*.lib")
foreach (LIBRARY IN LISTS WDK_LIBRARIES)
    get_filename_component(LIBRARY_NAME ${LIBRARY} NAME_WE)
    string(TOUPPER ${LIBRARY_NAME} LIBRARY_NAME)
    add_library(WDK::${LIBRARY_NAME} INTERFACE IMPORTED)
    set_property(TARGET WDK::${LIBRARY_NAME} PROPERTY INTERFACE_LINK_LIBRARIES ${LIBRARY})
endforeach (LIBRARY)
unset(WDK_LIBRARIES)

function(wdk_add_driver _target)
    cmake_parse_arguments(WDK "" "KMDF;WINVER;NTDDI_VERSION" "" ${ARGN})

    add_executable(${_target} ${WDK_UNPARSED_ARGUMENTS})

    set_target_properties(${_target} PROPERTIES SUFFIX ".sys")
    target_compile_options(${_target} PRIVATE ${WDK_COMPILE_FLAGS})

    target_compile_definitions(${_target} PRIVATE
        ${WDK_COMPILE_DEFINITIONS}
        $<$<CONFIG:Debug>:${WDK_COMPILE_DEFINITIONS_DEBUG}>
        _WIN32_WINNT=${WDK_WINVER}
    )

    target_link_options(${_target} PRIVATE ${WDK_LINK_FLAGS})

    if (WDK_NTDDI_VERSION)
        target_compile_definitions(${_target} PRIVATE NTDDI_VERSION=${WDK_NTDDI_VERSION})
    endif ()

    target_include_directories(${_target} SYSTEM PRIVATE
        "${WDK_ROOT}/Include/${WDK_INC_VERSION}/shared"
        "${WDK_ROOT}/Include/${WDK_INC_VERSION}/km"
        "${FINDWDK_DIR}/include"
    )

    target_link_libraries(${_target}
        WDK::NTOSKRNL
        #WDK::WMILIB
    )
endfunction()