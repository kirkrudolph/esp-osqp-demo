# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly

# Minimum version required
cmake_minimum_required(VERSION 3.5)

# Setup ESP toolchain
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Project name
project(esp-osqp CXX C)

# Project name
message("Top level CMakeLists.txt")

# Some standard CMake modules
# See https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html
include(ProcessorCount)
ProcessorCount(N)
message("Number of processors: ${N}")

# Some non-standard CMake modules


# Options
#option(ESP_OSQP_INCLUDE_EIGEN "Use Eigen" OFF)
#if(ESP_OSQP_INCLUDE_EIGEN)
#    include(eigen)
#endif()

# Include osqp (see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-third-party-cmake-projects-with-components)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------
# Set values of variables that control the build of `osqp`
set(EMBEDDED 2)
set(PYTHON 0)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)

# Create and import the library targets
#add_library(osqp STATIC osqp/src/osqp.c)
function(install)
endfunction()
function(export)
endfunction()
add_subdirectory(osqp)
function(add_library)
endfunction()

# Publicly link `osqp` to `main` component
#target_link_libraries(main PUBLIC osqp)
#target_link_libraries(${COMPONENT_LIB} PUBLIC osqp)
