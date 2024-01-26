add_library(nyx STATIC
	"../include/nyx/nyx.h"
	"../include/nyx/init.h" "init.cpp"
	"../include/nyx/app.h" "app.cpp"
)
set_target_properties(nyx PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)
target_include_directories(nyx PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(nyx PRIVATE "${PROJECT_SOURCE_DIR}/src")

if(WIN32)
	target_sources(nyx PRIVATE
		"platform/msw/msw.h"
		"platform/msw/string_util.h" "platform/msw/string_util.cpp"
		"platform/msw/window.h" "platform/msw/window.cpp"
	)
endif()