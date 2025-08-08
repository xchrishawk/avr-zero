#
# @file     CMakeLists.txt
# @brief    CMake configuration for the hw262-demo executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-07
#

cmake_minimum_required(VERSION 3.22)

# -- Executable Configuration --

set(EXECUTABLE_NAME     hw262-demo)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     hw262)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
