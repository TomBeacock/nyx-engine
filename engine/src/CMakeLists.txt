message(STATUS "Building engine...")

add_library(nyx STATIC
	"../include/nyx/nyx.h"
	"../include/nyx/init.h" "init.cpp"
	"../include/nyx/log.h"
	"../include/nyx/assert.h"

	"../include/nyx/system/app.h" "system/app.cpp"
	"../include/nyx/system/window.h" "system/window.cpp" 
	"system/window_impl.h" "system/window_impl.cpp"

	"../include/nyx/events.h"
	"../include/nyx/events/event.h" "../include/nyx/events/event.inl"
	"../include/nyx/events/key_codes.h"
	"../include/nyx/events/mouse_codes.h"
	
	"../include/nyx/math.h"
	"../include/nyx/math/constants.h"
	"../include/nyx/math/common.h"
	"../include/nyx/math/trigonometric.h"
	"../include/nyx/math/vector_func.h" "../include/nyx/math/vector_func.inl"
	"../include/nyx/math/vector2.h" "../include/nyx/math/vector2.inl" 
	"../include/nyx/math/vector3.h" "../include/nyx/math/vector3.inl"
	"../include/nyx/math/vector4.h" "../include/nyx/math/vector4.inl"

	"rendering/renderer.h" "rendering/renderer.cpp"
	"rendering/renderer_impl.h" 
 "rendering/renderer_impl.cpp")
set_target_properties(nyx PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)
target_include_directories(nyx PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(nyx PRIVATE "${PROJECT_SOURCE_DIR}/src")

string(LENGTH "${CMAKE_SOURCE_DIR}/" source_path_length)
target_compile_definitions(nyx PUBLIC SOURCE_PATH_LENGTH=${source_path_length})
target_compile_definitions(nyx PUBLIC NYX_RES_DIR="${PROJECT_SOURCE_DIR}/res/")

if(CMAKE_BUILD_TYPE)
	string(TOUPPER ${CMAKE_BUILD_TYPE} build_type)
endif()

# Enable/disable logging
if(build_type STREQUAL "DEBUG" OR build_type STREQUAL "RELWITHDEBINFO")
	target_compile_definitions(nyx PUBLIC NYX_LOGGING_ENABLED)
endif()

# Enable/disable assert
if(build_type STREQUAL "DEBUG")
	target_compile_definitions(nyx PUBLIC NYX_ASSERTS_ENABLED)
endif()

# Platform
if(WIN32)
	target_compile_definitions(nyx PUBLIC NYX_PLATFORM_MSW)
	target_sources(nyx PRIVATE
		"platform/msw/msw.h"
		"platform/msw/string_util.h" "platform/msw/string_util.cpp"
		"platform/msw/window_impl.h" "platform/msw/window_impl.cpp"
		"platform/msw/code_translation.h" "platform/msw/code_translation.cpp"
	)
endif()

if(D3D12)
	target_compile_definitions(nyx PUBLIC NYX_GRAPHICS_D3D12)
	target_link_libraries(nyx PUBLIC "d3d12.lib" "dxgi.lib" "d3dcompiler.lib" DirectXTK DirectX-Headers)
	target_sources(nyx PRIVATE
		"rendering/d3d12/renderer_impl.h" "rendering/d3d12/renderer_impl.cpp"
	 "rendering/d3d12/exception.h")
endif()

# Compiler
if(MSVC)
	target_compile_options(nyx PUBLIC /Zc:preprocessor)
endif()