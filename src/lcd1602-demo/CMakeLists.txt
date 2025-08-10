#
# @file     CMakeLists.txt
# @brief    CMake configuration for the lcd1602-demo executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-07
#

cmake_minimum_required(VERSION 3.22)

# -- Executable Configuration --

set(EXECUTABLE_NAME     lcd1602-demo)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     lcd1602)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
