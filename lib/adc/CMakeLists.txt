#
# @file     CMakeLists.txt
# @brief    CMake configuration for the adc library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-27
#

cmake_minimum_required(VERSION 3.22)

# -- Image Configuration --

set(LIBRARY_NAME     adc)
set(LIBRARY_SOURCE   adc.c adc.h)
set(LIBRARY_LIBS     utility)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
