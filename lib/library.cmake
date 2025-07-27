#
# @file     library.cmake
# @brief    Template CMake file for static libraries.
#
# @author   Chris Vig (chris@invictus.so)
# @date     2025-07-27
#
# Skeleton CMake file which can be included in a CMakeLists.txt file to set up a library.
# This allows quickly creating new libraries with a minimum amount of boilerplate.
#
# Example usage (CMakeLists.txt):
#
# ```
# cmake_minimum_required(VERSION 3.22)
# set(LIBRARY_NAME some-image)
# set(LIBRARY_SOURCE main.c some-file.c)
# set(LIBRARY_LIBS some-lib)
# include(${PROJECT_LIBRARY_DIR}/library.cmake)
# ```
#

# -- Project Setup --

# Define new project for library
project(${CMAKE_PROJECT_NAME}::${LIBRARY_NAME})

# -- Validate Arguments --

# Default to static library if not specified otherwise
if(NOT DEFINED LIBRARY_TYPE)
    set(LIBRARY_TYPE STATIC)
endif()

# Ensure required arguments are set
if(NOT DEFINED LIBRARY_NAME)
    message(FATAL_ERROR "LIBRARY_NAME must be defined!")
endif()
if(NOT DEFINED LIBRARY_TYPE)
    message(FATAL_ERROR "LIBRARY_TYPE must be defined!")
endif()
if(NOT DEFINED LIBRARY_SOURCE)
    message(FATAL_ERROR "LIBRARY_SOURCE must be defined!")
endif()

# -- Main Library --

# Define library
add_library(
    ${LIBRARY_NAME}
    ${LIBRARY_TYPE}
    ${LIBRARY_SOURCE}
)

# Add include directory
target_include_directories(
    ${LIBRARY_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Add libraries
target_link_libraries(
    ${LIBRARY_NAME}
    PUBLIC
    ${LIBRARY_LIBS}
)

# Explicitly define linker language for header-only libraries
set_target_properties(
    ${LIBRARY_NAME}
    PROPERTIES
        LINKER_LANGUAGE CXX
)