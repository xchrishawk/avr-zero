#
# @file     CMakeLists.txt
# @brief    CMake configuration for the zero library.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-27
#

cmake_minimum_required(VERSION 3.22)

# -- Library Configuration --

set(LIBRARY_NAME     zero)
set(LIBRARY_SOURCE   bit_ops.h pinout.h register.h utility.h)

# -- Set Up Project --

include(${PROJECT_LIBRARY_DIR}/library.cmake)
