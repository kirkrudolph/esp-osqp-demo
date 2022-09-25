# Minimum version required
cmake_minimum_required(VERSION 3.5)

# Setup ESP toolchain and project
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp-osqp CXX C)

# Project name
message("*** Top level CMakeLists.txt ***")

# See https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html
include(ProcessorCount)
ProcessorCount(N)
message("Number of processors (on current machine): ${N}")

# Include osqp (see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-third-party-cmake-projects-with-components)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------
# Set values of variables that control the build of `osqp`
set(EMBEDDED 2)
set(PYTHON 0)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)
add_subdirectory(osqp)
