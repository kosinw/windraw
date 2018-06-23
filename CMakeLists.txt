# Copyright (c) 2018 Kosi Nwabueze
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

cmake_minimum_required(VERSION 3.0.1)

if (NOT WIN32)	
	message(FATAL_ERROR "You must use Windows compilers in order to compile this library!")
endif()

project (windraw CXX)

add_library(windraw STATIC "")

target_sources(windraw
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/include/windraw/windraw.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/include/windraw/platform.hpp"
)

set_target_properties(windraw PROPERTIES LINKER_LANGUAGE CXX)

include (src/CMakeLists.txt)

target_include_directories(windraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(windraw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(example)