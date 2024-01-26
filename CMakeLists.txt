cmake_minimum_required(VERSION 3.14)

project("nyx")

string(APPEND NYX_SOURCE_DIR "${PROJECT_SOURCE_DIR}")

option(NYX_BUILD_EXAMPLES "Build example applications" on)
option(NYX_BUILD_TESTS "Build test suite" on)

add_subdirectory("extern")
add_subdirectory("src")

if(NYX_BUILD_EXAMPLES)
	message(STATUS "Building examples...")
	add_subdirectory("examples")
endif()

if(NYX_BUILD_TESTS)
	message(STATUS "Building tests...")
	add_subdirectory("tests")
endif()