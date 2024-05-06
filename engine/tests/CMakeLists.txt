project(tests)

add_executable(tests
"platform/msw/string_util.cpp"
"math/vector_func.cpp" "math/vector2.cpp" "math/vector3.cpp" "math/vector4.cpp"
)
target_link_libraries(tests PRIVATE nyx GTest::gtest_main)
target_include_directories(tests PRIVATE "${NYX_SOURCE_DIR}/src")
set_target_properties(tests PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED on)

include(GoogleTest)
gtest_discover_tests(tests)