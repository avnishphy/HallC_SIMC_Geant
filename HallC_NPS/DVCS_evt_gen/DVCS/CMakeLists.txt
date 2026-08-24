cmake_minimum_required(VERSION 3.10)
project(DVCS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# Allow user to provide path to the pre-built NPS_SOFT installation
# Example: cmake .. -DNPS_SOFT_ROOT=/work/hallc/nps/singhav/geant4_simc/NPS_SOFT
if(NOT DEFINED NPS_SOFT_ROOT AND DEFINED ENV{NPS_SOFT_ROOT})
  set(NPS_SOFT_ROOT $ENV{NPS_SOFT_ROOT})
endif()
if(NOT NPS_SOFT_ROOT)
  message(WARNING "NPS_SOFT root not set. Set -DNPS_SOFT_ROOT=/path/to/NPS_SOFT to link against NPS_SOFT libs.")
endif()

# Find Geant4 (UI/vis optional)
find_package(Geant4 REQUIRED ui_all vis_all)
if(NOT Geant4_FOUND)
  message(FATAL_ERROR "Geant4 not found. Source geant4 environment or set Geant4_DIR.")
endif()
include(${Geant4_USE_FILE})

# Find ROOT
find_package(ROOT REQUIRED COMPONENTS RIO Tree Core Hist)
if(NOT ROOT_FOUND)
  message(FATAL_ERROR "ROOT not found.")
endif()
message(STATUS "ROOT_INCLUDE_DIRS=${ROOT_INCLUDE_DIRS}")

# Add include directories and sources
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${ROOT_INCLUDE_DIRS}
)

file(GLOB DVCS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB DVCS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")

# Create the executable
add_executable(DVCS ${DVCS_SRCS} ${DVCS_HEADERS})

get_filename_component(DVCS_REPOSITORY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)

target_compile_definitions(DVCS PRIVATE
  DVCS_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
  DVCS_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}"
  DVCS_REPOSITORY_DIR="${DVCS_REPOSITORY_DIR}"
)

# Link Geant4 and ROOT
# Older Geant4 uses ${Geant4_LIBRARIES}; include file already sets these. We'll link with them.
target_include_directories(DVCS PRIVATE ${Geant4_INCLUDE_DIRS})
target_link_libraries(DVCS PRIVATE ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# ===== Link to NPS_SOFT (pre-built) =====
# We try to find common libs used by the code. Adjust names if your NPS_SOFT libs differ.
if(NPS_SOFT_ROOT)
  # add include dir from NPS_SOFT (headers are often at NPS_SOFT/)
  target_include_directories(DVCS PRIVATE ${NPS_SOFT_ROOT})

  # try to locate common libraries in that folder
  # likely library file names: libDVCS.so, libTDVCSGlobal2.so, libTDVCSGlobal2.a, etc.
  find_library(NPS_LIB_DVCS NAMES libDVCS DVCS PATHS ${NPS_SOFT_ROOT} ${NPS_SOFT_ROOT}/lib /usr/local/lib NO_DEFAULT_PATH)
  find_library(NPS_LIB_TDVCS NAMES libTDVCSGlobal2 TDVCSGlobal2 PATHS ${NPS_SOFT_ROOT} ${NPS_SOFT_ROOT}/lib /usr/local/lib NO_DEFAULT_PATH)

  if(NPS_LIB_DVCS)
    message(STATUS "Found NPS libDVCS: ${NPS_LIB_DVCS}")
    target_link_libraries(DVCS PRIVATE ${NPS_LIB_DVCS})
  else()
    message(WARNING "libDVCS not found under ${NPS_SOFT_ROOT}. If you need NPS_SOFT symbols, set NPS_SOFT_ROOT to the correct folder.")
  endif()

  if(NPS_LIB_TDVCS)
    message(STATUS "Found NPS libTDVCSGlobal2: ${NPS_LIB_TDVCS}")
    target_link_libraries(DVCS PRIVATE ${NPS_LIB_TDVCS})
  else()
    message(WARNING "libTDVCSGlobal2 not found under ${NPS_SOFT_ROOT}.")
  endif()

  # Set rpath so executable can find the NPS_SOFT libraries at runtime (no LD_LIBRARY_PATH required)
  get_filename_component(_nps_dir ${NPS_SOFT_ROOT} ABSOLUTE)
  set_target_properties(DVCS PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${_nps_dir}"
    INSTALL_RPATH_USE_LINK_PATH TRUE
  )
endif()

# Additional platform/linker flags (if required)
if(UNIX)
  target_link_libraries(DVCS PRIVATE pthread dl m)
endif()

# Copy runtime macros into the build tree so UI commands can find them.
# The canonical runtime location is build/macros/.  Flat build/*.mac copies are
# retained for compatibility with older launch habits and existing notes.
set(DVCS_RUNTIME_MACROS
  macros/vis.mac
  macros/vis_setup.mac
  macros/vis_single.mac
  macros/vis_sequential.mac
  macros/vis_gpt.mac
  macros/test.mac
  macros/run_batch.mac
)

set(DVCS_BUILD_MACRO_DIR ${CMAKE_CURRENT_BINARY_DIR}/macros)
file(MAKE_DIRECTORY ${DVCS_BUILD_MACRO_DIR})
foreach(_macro ${DVCS_RUNTIME_MACROS})
  get_filename_component(_macro_name ${_macro} NAME)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${_macro}
    ${DVCS_BUILD_MACRO_DIR}/${_macro_name}
    COPYONLY
  )
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${_macro}
    ${CMAKE_CURRENT_BINARY_DIR}/${_macro_name}
    COPYONLY
  )
endforeach()

# Installation (optional)
install(TARGETS DVCS RUNTIME DESTINATION bin)
