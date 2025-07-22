#
# @file     CMakeLists.txt
# @brief    CMake configuration for the exakey executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-21
#

cmake_minimum_required(VERSION 3.22)

# -- Image Configuration --

set(EXECUTABLE_NAME     exakey)
set(EXECUTABLE_SOURCE   gpio.c main.c)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
