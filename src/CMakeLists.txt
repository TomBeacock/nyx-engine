add_library(nyx STATIC
	"../include/nyx/nyx.h"
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
)
set_target_properties(nyx PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)
target_include_directories(nyx PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(nyx PRIVATE "${PROJECT_SOURCE_DIR}/src")

if(WIN32)
	target_compile_definitions(nyx PUBLIC NYX_PLATFORM_MSW)
	target_sources(nyx PRIVATE
		"platform/msw/msw.h"
		"platform/msw/string_util.h" "platform/msw/string_util.cpp"
		"platform/msw/window_impl.h" "platform/msw/window_impl.cpp"
		"platform/msw/code_translation.h" "platform/msw/code_translation.cpp"
	)
endif()