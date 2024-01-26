add_executable(hello-world "src/hello-world.cpp")
target_link_libraries(hello-world PRIVATE nyx)
set_target_properties(hello-world PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)

if(WIN32)
	set_target_properties(hello-world PROPERTIES WIN32_EXECUTABLE on)
	target_link_options(hello-world PRIVATE "/entry:mainCRTStartup" "/subsystem:$<IF:$<CONFIG:Debug>,console,windows>")
endif()