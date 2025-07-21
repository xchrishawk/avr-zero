#
# @file     executable.cmake
# @brief    Template CMake file for executable images.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-21
#
# Skeleton CMake file which can be included in a CMakeLists.txt file to set up an executable.
# This allows quickly creating new executables with a minimum amount of boilerplate.
#
# Example usage (CMakeLists.txt):
#
# ```
# cmake_minimum_required(VERSION 3.22)
# set(EXECUTABLE_NAME some-image)
# set(EXECUTABLE_SOURCE main.c some-file.c)
# set(EXECUTABLE_LIBS some-lib)
# include(${PROJECT_SRC_DIR}/executable.cmake)
# ```
#

# -- Project Setup --

# Define new subproject for executable
project(${CMAKE_PROJECT_NAME}::${EXECUTABLE_NAME})

# -- Validate Arguments --

# Default to no libraries if not specified otherwise
if(NOT DEFINED EXECUTABLE_LIBS)
    set(EXECUTABLE_LIBS "")
endif()

# Ensure required arguments are set
if(NOT DEFINED EXECUTABLE_NAME)
    message(FATAL_ERROR "EXECUTABLE_NAME must be defined!")
endif()
if(NOT DEFINED EXECUTABLE_SOURCE)
    message(FATAL_ERROR "EXECUTABLE_SOURCE must be defined!")
endif()
if(NOT DEFINED EXECUTABLE_LIBS)
    message(FATAL_ERROR "EXECUTABLE_LIBS must be defined!")
endif()

# -- Main Executable --

# Define executable
add_executable(
    ${EXECUTABLE_NAME}
    ${EXECUTABLE_SOURCE}
)

# Add libraries
target_link_libraries(
    ${EXECUTABLE_NAME}
    ${EXECUTABLE_LIBS}
)

# Set custom filename for executable
set_target_properties(
    ${EXECUTABLE_NAME}
    PROPERTIES
        OUTPUT_NAME ${EXECUTABLE_NAME}.elf
)

# -- IHEX Executable --

# Add command for IHEX output
add_custom_command(
    OUTPUT ${EXECUTABLE_NAME}.ihex
    DEPENDS ${PROJECT_BIN_DIR}/${EXECUTABLE_NAME}.elf
    COMMAND ${AVR_STRIP}
    ARGS ${EXECUTABLE_NAME}.elf
    COMMAND ${AVR_OBJCOPY}
    ARGS -R .eeprom -O ihex ${EXECUTABLE_NAME}.elf ${EXECUTABLE_NAME}.ihex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Add target for IHEX output so that it gets built
add_custom_target(
    ${EXECUTABLE_NAME}-ihex
    ALL
    DEPENDS ${EXECUTABLE_NAME}.ihex
)

# Clean additional support files
set_directory_properties(
    PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_BIN_DIR}/${EXECUTABLE_NAME}.ihex
)
