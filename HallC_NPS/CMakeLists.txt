cmake_minimum_required(VERSION 3.10)
project(HallC_NPS LANGUAGES CXX)

# default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")

# Option: user can tell us where NPS_SOFT installation lives.
# Example usage:
#  cmake .. -DNPS_SOFT_ROOT=/path/to/NPS_SOFT
if(NOT DEFINED NPS_SOFT_ROOT AND DEFINED ENV{NPS_SOFT_ROOT})
  set(NPS_SOFT_ROOT $ENV{NPS_SOFT_ROOT})
endif()
if(NOT NPS_SOFT_ROOT)
  message(STATUS "NPS_SOFT root not provided (set -DNPS_SOFT_ROOT=/path/to/NPS_SOFT). Attempting to proceed without it.")
else()
  message(STATUS "NPS_SOFT root: ${NPS_SOFT_ROOT}")
endif()

# We will build the DVCS example (it will find Geant4 & ROOT itself):
add_subdirectory(DVCS_evt_gen/DVCS)
