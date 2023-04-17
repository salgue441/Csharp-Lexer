cmake_minimum_required(VERSION 3.0)

project(Lexer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lexer main.cpp)

target_include_directories(Lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(Lexer PUBLIC -Wall -Wextra -Werror)
