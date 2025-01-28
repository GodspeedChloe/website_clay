cmake_minimum_required(VERSION 3.28)
project(blog)
set(CMAKE_C_STANDARD 99)

add_executable(blog blog.c)

target_compile_options(blog PUBLIC -Wall -Werror -Wno-unknown-pragmas)
target_include_directories(blog PUBLIC .)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")