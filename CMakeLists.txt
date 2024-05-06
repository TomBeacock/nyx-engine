cmake_minimum_required(VERSION 3.14)

project("nyx")

add_subdirectory("engine")

if(NYX_BUILD_EXAMPLES)
	message(STATUS "Building examples...")
	add_subdirectory("examples")
endif()