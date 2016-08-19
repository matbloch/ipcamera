cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Release as default
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

project (ipcamera C CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# all errors
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# set cmake module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

message(${CMAKE_MODULE_PATH})

# The version number.
set (SFM_VERSION_MAJOR 0)
set (SFM_VERSION_MINOR 1)

find_package(OpenCV 2.4 REQUIRED)
find_package(dlib REQUIRED)

# Set output folders
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create "${CMAKE_BINARY_DIR}/bin"
# ToDo: check why this is needed!
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/pictures")

# Add the actual source files
add_subdirectory (src)
