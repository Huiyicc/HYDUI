cmake_minimum_required(VERSION 3.16)
project(HYDUI)

set(CMAKE_CXX_STANDARD 20)

# include
include_directories( ${CMAKE_CURRENT_LIST_DIR}/include )

set(SDL2_PATH "D:/SDK/MSYS2/mingw64/installd/SDL2")
include_directories( ${SDL2_PATH}/include )
list(APPEND CMAKE_PREFIX_PATH ${SDL2_PATH})

# Dependent Libraries
file(GLOB_RECURSE lib_source
        ${CMAKE_CURRENT_LIST_DIR}/src/*.*
)

# library

add_library(HYDUI ${lib_source})
target_link_directories(HYDUI PUBLIC ${SDL2_PATH}/lib)
target_link_libraries(HYDUI PUBLIC
        SDL2
        SDL2_image
)
if(CMAKE_HOST_UNIX)
    # linux独有库
elseif(CMAKE_HOST_WIN32)
    # windows独有库
    target_link_libraries(HYDUI PUBLIC -lws2_32 -lwinmm -limm32 -lsetupapi -lVersion -static-libgcc -static-libstdc++ -static -lpthread)
    set_target_properties(HYDUI PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# test

add_executable(exp_test ${CMAKE_CURRENT_LIST_DIR}/test/winmain/main.cpp)

target_link_libraries(exp_test
        HYDUI
)
