message(STATUS "Building engine...")

add_library(nyx STATIC
	"../include/nyx/nyx.h"
	"../include/nyx/base.h"
	"../include/nyx/log.h"
	"../include/nyx/assert.h"
	"../include/nyx/types.h"
	"../include/nyx/init.h" "init.cpp"

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
	"../include/nyx/math/quaternion.h" "../include/nyx/math/quaternion.inl"
	"../include/nyx/math/quaternion_func.h" "../include/nyx/math/quaternion_func.inl"
	"../include/nyx/math/matrix_func.h" "../include/nyx/math/matrix_func.inl"
	"../include/nyx/math/matrix_transform.h" "../include/nyx/math/matrix_transform.inl"
	"../include/nyx/math/matrix4x4.h" "../include/nyx/math/matrix4x4.inl"

	"../include/nyx/string/string_util.h" "string/string_util.cpp"

	"rendering/renderer.h" "rendering/renderer.cpp"
	"rendering/renderer_impl.h" "rendering/renderer_impl.cpp"
)
set_target_properties(nyx PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)
target_include_directories(nyx PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(nyx PRIVATE "${PROJECT_SOURCE_DIR}/src")

string(LENGTH "${PROJECT_SOURCE_DIR}/" engine_source_path_length)
target_compile_definitions(nyx PUBLIC NYX_ENGINE_SOURCE_PATH_LENGTH=${engine_source_path_length})
target_compile_definitions(nyx PUBLIC NYX_ENGINE_RES_DIR="${PROJECT_SOURCE_DIR}/res/")

if(CMAKE_BUILD_TYPE)
	string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
endif()

# Enable/disable debug
if(build_type STREQUAL "debug")
	target_compile_definitions(nyx PUBLIC NYX_DEBUG)
endif()

# Enable/disable logging
if(build_type STREQUAL "relwithdebinfo")
	target_compile_definitions(nyx PUBLIC NYX_DEBUG_INFO_ONLY)
endif()

# Platform
if(WIN32)
	target_compile_definitions(nyx PUBLIC NYX_PLATFORM_MSW)
	target_sources(nyx PRIVATE
		"system/msw/msw.h"
		"system/msw/window_impl.h" "system/msw/window_impl.cpp"
		"system/msw/code_translation.h" "system/msw/code_translation.cpp"
	)
endif()

if(D3D12)
	target_compile_definitions(nyx PUBLIC NYX_GRAPHICS_D3D12)
	target_link_libraries(nyx PUBLIC "d3d12.lib" "dxgi.lib" "d3dcompiler.lib" DirectXTK DirectX-Headers)
	target_sources(nyx PRIVATE
		"rendering/d3d12/exception.h"
		"rendering/d3d12/renderer_impl.h" "rendering/d3d12/renderer_impl.cpp"
	)
endif()

# Compiler
if(MSVC)
	target_compile_options(nyx PUBLIC /Zc:preprocessor)
endif()