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
message("-- Number of processors (on current machine): ${N}")

