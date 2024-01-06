cmake_minimum_required(VERSION 3.14)

project("nyx")

option(NYX_BUILD_EXAMPLES "Build example applications" on)

add_subdirectory("src")

if(NYX_BUILD_EXAMPLES)
	message(STATUS "Building examples")
	add_subdirectory("examples")
endif()