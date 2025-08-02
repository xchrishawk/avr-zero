#
# @file     CMakeLists.txt
# @brief    CMake configuration for the powerbar-switcher executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-01
#

cmake_minimum_required(VERSION 3.22)

# -- Executable Configuration --

set(EXECUTABLE_NAME     powerbar-switcher)
set(EXECUTABLE_SOURCE   main.c)
set(EXECUTABLE_LIBS     gpio usart)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
