cmake_minimum_required(VERSION 3.28)
project(blog)
set(CMAKE_C_STANDARD 99)

#include(${CMAKE_CURRENT_SOURCE_DIR}/clay-0.12/CMakeLists.txt)

add_executable(${PROJECT_NAME} blog.c)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

target_compile_options(blog PUBLIC)
target_include_directories(blog PUBLIC .)

target_link_libraries(blog PUBLIC raylib)

set(CMAKE_C_FLAGS_DEBUG "-Wall -Werror -Wno-error=missing-braces -DCLAY_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3")

add_custom_command(
        TARGET blog POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources)
