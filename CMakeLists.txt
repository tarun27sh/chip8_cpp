cmake_minimum_required(VERSION 3.5.1)
project(chip8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set (CMAKE_CXX_FLAGS_DEBUG 
    "${CMAKE_CXX_FLAGS_DEBUG}         \
    -Wall -Wextra                     \
    -fno-omit-frame-pointer           \
    -fsanitize=thread")
    #-Wpedantic -Werror  \
    #    -fsanitize=memory") # not supported by gcc
    #    -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG
    "${CMAKE_LINKER_FLAGS_DEBUG}      \
    -fno-omit-frame-pointer           \
    -fsanitize=thread")
    #-fsanitize=memory") # not supported by gcc
    #-fsanitize=address")

    add_custom_target(graphviz ALL
    COMMAND ${CMAKE_COMMAND} "--graphviz=foo.dot" .
    COMMAND dot -Tpng foo.dot -o foo.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )

# generate shared lib
add_subdirectory(lib)

# generate executable
add_subdirectory(src)


# gtest
add_subdirectory(test)
