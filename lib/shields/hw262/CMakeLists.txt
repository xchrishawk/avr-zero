#
# @file     CMakeLists.txt
# @brief    CMake configuration for the hw262 library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-07
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME    hw262)
set(LIBRARY_SOURCE  hw262.c hw262.h)
set(LIBRARY_LIBS    gpio zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
