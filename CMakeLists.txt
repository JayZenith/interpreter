cmake_minimum_required(VERSION 3.20)
project(testing)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Adding coverage compile flags")
    add_compile_options(-O0 -g --coverage -fprofile-arcs -ftest-coverage)
    add_link_options(--coverage)
endif()


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

# add_library(tunnl_lib src/main.cpp)
add_library(tunnl_lib
    src/main.cpp
    src/interpreter.cpp
    src/parser.cpp
    src/tokenization.cpp
)
target_include_directories(tunnl_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_subdirectory(external/googletest googletest-build)

# # Test executable
# add_executable(interpreter_tests tests/test_interpreter.cpp
# )

# # Tell CMake where to find headers
# target_include_directories(interpreter_tests PRIVATE
#     ${PROJECT_SOURCE_DIR}/src
# )

# target_link_libraries(interpreter_tests PRIVATE tunnl_lib gtest_main)

add_executable(interpreter_tests
    tests/test_interpreter.cpp
)

target_link_libraries(interpreter_tests PRIVATE tunnl_lib gtest_main)
target_include_directories(interpreter_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)



# Tell CTest to run your executable (optional, can be skipped)
enable_testing()
add_test(NAME RunInterpreterTests COMMAND interpreter_tests)

# Source files (header-only generators are included via main.cpp)
add_executable(testy 
    src/main.cpp
    src/tokenization.cpp
    src/parser.cpp
    src/interpreter.cpp
)

target_link_libraries(testy PRIVATE tunnl_lib)

