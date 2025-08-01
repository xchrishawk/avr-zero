#
# @file     CMakeLists.txt
# @brief    CMake configuration for the gpio library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-27
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME     gpio)
set(LIBRARY_SOURCE   gpio.c gpio.h)
set(LIBRARY_LIBS     zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
