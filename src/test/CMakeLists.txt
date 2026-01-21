cmake_minimum_required(VERSION 3.16)

project(DyverTest)

add_compile_options(-Wpedantic -Wall -Wextra)

add_executable(
    ${PROJECT_NAME}
    test.cpp
    ../amp_distribution.cpp
    ../rov.cpp
    ../networking/socket_helper.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${eigen_SOURCE_DIR}
    ${sdl_SOURCE_DIR}/include
    ${matplotplusplus_SOURCE_DIR}/source
    ${CMAKE_BINARY_DIR}/_deps/matplotplusplus-build/source/matplot/
    ..
)
