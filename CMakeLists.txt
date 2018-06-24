# Copyright (c) 2018 Kosi Nwabueze
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

# target_sources is required so 3.0.1 is the minimum required version
cmake_minimum_required(VERSION 3.0.1)

# Throw error message if platform is not Windows
if (NOT WIN32)
	message(FATAL_ERROR "You must use MinGW or VC++ compilers in order to compile this library!")
endif()

# Set the project name to windraw
project (windraw CXX)

# Create a static library and include subdirectories
add_library(windraw STATIC "")
include (src/windraw/CMakeLists.txt)

# Use unicode versions of functions
add_definitions(-DUNICODE=1 -D_UNICODE=1)

# Don't include unneccessary things in <Windows.h>
add_definitions(-DWIN32_LEAN_AND_MEAN)

# If debug add DEBUG macro
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")


# Add specific defines to determine which OS is being used
if (CMAKE_COMPILER_IS_GNUCXX AND WIN32)
	add_definitions(-DWD_PLATFORM_MINGW=1)	
elseif (MSVC)
	add_definitions(-DWD_PLATFORM_MSVC=1)

	add_definitions(-DWD_DIRECT2D_ENABLED=1)
	set (D2D_ENABLED TRUE)
	
	add_definitions(-DWD_GDIPLUS_ENABLED=1)
	set (GDIPLUS_ENABLED TRUE)
endif()

# Use the C++ linker with windraw
set_target_properties(windraw PROPERTIES LINKER_LANGUAGE CXX)

# Set the include files in the src directory with public linkage
target_include_directories(windraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the example subdirectory
add_subdirectory(example)