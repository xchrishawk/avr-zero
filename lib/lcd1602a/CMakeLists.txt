#
# @file     CMakeLists.txt
# @brief    CMake configuration for the lcd1602a library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-27
#

cmake_minimum_required(VERSION 3.22)

# -- Image Configuration --

set(LIBRARY_NAME     lcd1602a)
set(LIBRARY_SOURCE   lcd1602a.c lcd1602a.h)
set(LIBRARY_LIBS     adc gpio utility)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
