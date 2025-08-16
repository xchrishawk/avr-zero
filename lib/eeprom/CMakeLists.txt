#
# @file     CMakeLists.txt
# @brief    CMake configuration for the eeprom library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-16
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME     eeprom)
set(LIBRARY_SOURCE   eeprom.c eeprom.h)
set(LIBRARY_LIBS     zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
