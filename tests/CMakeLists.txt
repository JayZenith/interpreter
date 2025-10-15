# Give a binary dir to avoid out-of-tree issue
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest-build)

# Test executable
add_executable(interpreter_tests test_interpreter.cpp)
target_link_libraries(interpreter_tests PRIVATE tunnl_lib gtest_main)
