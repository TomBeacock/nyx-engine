project(extern)

if(NYX_BUILD_TESTS)
	set(gtest_force_shared_crt on CACHE bool "" FORCE)
	set(INSTALL_GTEST off CACHE bool "" FORCE)
	add_subdirectory("googletest")
endif()