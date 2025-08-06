#
# @file     CMakeLists.txt
# @brief    CMake configuration for the powerbar-switcher executable.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-08-01
#

cmake_minimum_required(VERSION 3.22)

# -- Check Device --

if(NOT "${DEVICE_MCU}" STREQUAL "atmega328p")
    message(STATUS "Skipping powerbar-switcher due to incorrect architecture.")
    return()
endif()

# -- Executable Configuration --

set(EXECUTABLE_NAME     powerbar-switcher)
set(EXECUTABLE_SOURCE   com.c com.h event.c event.h main.c powerbar.c powerbar.h)
set(EXECUTABLE_LIBS     gpio usart zero)

# -- Set Up Project --

include(${PROJECT_EXECUTABLE_DIR}/executable.cmake)
