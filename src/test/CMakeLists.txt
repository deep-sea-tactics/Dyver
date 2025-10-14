cmake_minimum_required(VERSION 3.16)

project(DyverTest)

add_executable(
    ${PROJECT_NAME}
    test.cpp
    ../amp_distribution.cpp
)