# This is the build system for Dyver. If you require assistance
# with adding libraries and dependencies, please contact a project manager
# (Most likely Yevgenya Coonan)

cmake_minimum_required(VERSION 3.16)
project(Dyver VERSION 0.0.0 LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.0
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_Declare(
    dss
    GIT_REPOSITORY https://github.com/Inotrandom/deep-sea-shell.git
    GIT_TAG master
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_MakeAvailable(eigen)
FetchContent_MakeAvailable(dss)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    src/rov.cpp
    src/thruster.cpp
    src/BindableAction.cpp
    ${dss_SOURCE_DIR}/source/runtime.cpp
    ${dss_SOURCE_DIR}/source/cli.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${eigen_SOURCE_DIR}/Eigen
    ${dss_SOURCE_DIR}/source
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    DSS
)