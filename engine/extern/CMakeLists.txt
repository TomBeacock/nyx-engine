project(extern)

if(NYX_BUILD_TESTS)
	set(gtest_force_shared_crt on CACHE BOOL "" FORCE)
	set(INSTALL_GTEST off CACHE BOOL "" FORCE)
	add_subdirectory("googletest")
endif()

if(D3D12)
	add_subdirectory("directXTK")
	add_subdirectory("directX-headers")
endif()