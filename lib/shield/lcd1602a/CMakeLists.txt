#
# @file     CMakeLists.txt
# @brief    CMake configuration for the shields/lcd1602a library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-16
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME    shield-lcd1602a)
set(LIBRARY_SOURCE  shield-lcd1602a.c shield-lcd1602a.h)
set(LIBRARY_LIBS    adc gpio lcdtext zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
