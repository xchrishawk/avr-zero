#
# @file     CMakeLists.txt
# @brief    CMake configuration for the adc-demo executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-10
#

cmake_minimum_required(VERSION 3.22)

# -- Executable Configuration --

set(EXECUTABLE_NAME     adc-demo)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     adc lcd1602 zero)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
