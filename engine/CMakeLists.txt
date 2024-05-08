cmake_minimum_required(VERSION 3.14)

project("nyx-engine")

string(APPEND NYX_SOURCE_DIR "${PROJECT_SOURCE_DIR}")

option(NYX_BUILD_EXAMPLES "Build example applications" on)
option(NYX_BUILD_TESTS "Build test suite" on)

if(WIN32)
	set(D3D12 on)
endif()

add_subdirectory("extern")
add_subdirectory("src")

if(NYX_BUILD_TESTS)
	message(STATUS "Building tests...")
	add_subdirectory("tests")
endif()