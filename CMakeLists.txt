cmake_minimum_required(VERSION 3.20)

# Project name
project(Lexer)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS)

# Main target
add_executable(Lexer 
    src/main.cpp
)

target_include_directories(Lexer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(Lexer PUBLIC 
    -Wall 
    -Wextra 
    -Werror
)

# Google Test Library
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add tests target
add_executable(tests
    tests/token_test.cpp
    src/token.cpp
)

target_include_directories(tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tests PUBLIC 
    gtest_main
)

# Register test
include(GoogleTest)
gtest_discover_tests(tests)

# Custom command for generating output directory and running Lexer
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/output
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/output
    COMMAND Lexer ../input
    DEPENDS ../input Lexer
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Using the custom command as a dependency for the run target
add_custom_target(run
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/output
)

