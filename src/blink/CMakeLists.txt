#
# @file     CMakeLists.txt
# @brief    CMake configuration for the blink executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-01
#

cmake_minimum_required(VERSION 3.22)

# -- Image Configuration --

set(EXECUTABLE_NAME     blink)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     gpio)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
