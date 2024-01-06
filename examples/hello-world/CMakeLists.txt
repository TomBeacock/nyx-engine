add_executable(hello-world "src/hello-world.cpp")
target_link_libraries(hello-world PRIVATE nyx)

if(WIN32)
	set_target_properties(hello-world PROPERTIES WIN32_EXECUTABLE on)
	target_link_options(hello-world PRIVATE "/entry:mainCRTStartup" "/subsystem:$<IF:$<CONFIG:Debug>,console,windows>")
endif()