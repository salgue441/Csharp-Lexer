cmake_minimum_required(VERSION 3.20)

project(Lexer)

# Enable C++20 support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable C++20 modules support for clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules -fimplicit-modules -fimplicit-module-maps")
endif()


# Program executable
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
    -fmodules-ts
)

# Include Google Test
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

    tests/lexer_test.cpp
    src/lexer.cpp
)

target_include_directories(tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(tests PUBLIC 
    -Wall 
    -Wextra 
    -Werror
    -fmodules-ts
)

target_link_libraries(tests PUBLIC 
    gtest_main
)

# Register tests
include(GoogleTest)
gtest_discover_tests(tests)

# Add a custom target for running the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_BINARY_DIR}/tests
    DEPENDS tests
)

# Add a custom target for running the program
add_custom_target(run_lexer
    COMMAND ${CMAKE_BINARY_DIR}/Lexer ../input ../output
    DEPENDS Lexer
)

# Set the default target to run the program
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Lexer)