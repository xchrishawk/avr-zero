#
# @file     CMakeLists.txt
# @brief    CMake configuration for the lcd1602 library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-08
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME     lcd1602)
set(LIBRARY_SOURCE   lcd1602.c lcd1602.h)
set(LIBRARY_LIBS     gpio zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
