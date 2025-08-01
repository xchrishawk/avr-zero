#
# @file     CMakeLists.txt
# @brief    CMake configuration for the usart library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-31
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME    usart)
set(LIBRARY_SOURCE  usart.c usart.h)
set(LIBRARY_LIBS    zero)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
