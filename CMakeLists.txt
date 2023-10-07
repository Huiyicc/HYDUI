cmake_minimum_required(VERSION 3.26)
project(HYDUI)

set(CMAKE_CXX_STANDARD 20)

# include
include_directories( ${CMAKE_CURRENT_LIST_DIR}/include )

# Dependent Libraries
file(GLOB_RECURSE lib_source
        ${CMAKE_CURRENT_LIST_DIR}/src/*.*
)

# library

add_library(HYDUI ${lib_source})
target_link_libraries(HYDUI
        SDL2
)

# test

add_executable(exp_test ${CMAKE_CURRENT_LIST_DIR}/test/winmain/main.cpp)
target_link_libraries(exp_test
        HYDUI
)
