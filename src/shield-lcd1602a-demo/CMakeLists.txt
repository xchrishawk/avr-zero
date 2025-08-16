#
# @file     CMakeLists.txt
# @brief    CMake configuration for the shield-lcd1602a-demo executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-16
#

cmake_minimum_required(VERSION 3.22)

# -- Executable Configuration --

set(EXECUTABLE_NAME     shield-lcd1602a-demo)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     shield-lcd1602a)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
