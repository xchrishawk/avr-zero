#
# @file     CMakeLists.txt
# @brief    CMake configuration for the lcdtext library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-08
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME     lcdtext)
set(LIBRARY_SOURCE   lcdtext.c lcdtext.h)
set(LIBRARY_LIBS     gpio zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
