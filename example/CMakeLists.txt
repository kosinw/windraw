# Copyright (c) 2018 Kosi Nwabueze
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

project (example)

add_executable(example WIN32 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(example PUBLIC windraw)

if (MSVC)
	set_target_properties(example PROPERTIES LINK_FLAGS "/subsystem:WINDOWS /entry:mainCRTStartup")
endif()