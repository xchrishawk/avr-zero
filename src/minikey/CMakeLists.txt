#
# @file     CMakeLists.txt
# @brief    CMake configuration for the minikey executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-29
#

cmake_minimum_required(VERSION 3.22)

# -- Image Configuration --

set(EXECUTABLE_NAME             minikey)
set(EXECUTABLE_SOURCE           main.S)
set(EXECUTABLE_LINK_OPTIONS     -nostartfiles)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
