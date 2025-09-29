# CMakeLists.txt for DELPHI EDM4hep custom data model
# This file handles the generation of C++ classes from YAML schema

cmake_minimum_required(VERSION 3.16)

# Find required packages for data model generation
find_package(podio REQUIRED)

# Set the data model name
set(DATAMODEL_NAME "delphi_edm4hep")

# Define the YAML schema file
set(SCHEMA_FILE "${CMAKE_CURRENT_SOURCE_DIR}/delphi_edm4hep.yaml")

# Define output directories
set(DATAMODEL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(DATAMODEL_INCLUDE_DIR "${DATAMODEL_OUTPUT_DIR}/include")
set(DATAMODEL_SOURCE_DIR "${DATAMODEL_OUTPUT_DIR}/src")

# Create output directories
file(MAKE_DIRECTORY ${DATAMODEL_OUTPUT_DIR})
file(MAKE_DIRECTORY ${DATAMODEL_INCLUDE_DIR})
file(MAKE_DIRECTORY ${DATAMODEL_SOURCE_DIR})

# Generate the data model classes from YAML
# This uses the podio_generate_datamodel function
podio_generate_datamodel(
  ${DATAMODEL_NAME}
  ${SCHEMA_FILE}
  HEADERS_DIR ${DATAMODEL_INCLUDE_DIR}
  SOURCES_DIR ${DATAMODEL_SOURCE_DIR}
  IO_BACKEND_HANDLERS ROOT
)

# Create a library from the generated sources
file(GLOB DATAMODEL_SOURCES "${DATAMODEL_SOURCE_DIR}/*.cc")
file(GLOB DATAMODEL_HEADERS "${DATAMODEL_INCLUDE_DIR}/${DATAMODEL_NAME}/*.h")

add_library(${DATAMODEL_NAME} SHARED ${DATAMODEL_SOURCES})

# Set target properties
target_include_directories(${DATAMODEL_NAME} 
  PUBLIC 
    $<BUILD_INTERFACE:${DATAMODEL_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Link against required libraries
target_link_libraries(${DATAMODEL_NAME} 
  PUBLIC 
    podio::podio
    ROOT::Core
    ROOT::RIO
    ROOT::Tree
)

# Set compile features
target_compile_features(${DATAMODEL_NAME} PUBLIC cxx_std_17)

# Installation rules
install(TARGETS ${DATAMODEL_NAME}
  EXPORT ${DATAMODEL_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY ${DATAMODEL_INCLUDE_DIR}/${DATAMODEL_NAME}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT ${DATAMODEL_NAME}Targets
  FILE ${DATAMODEL_NAME}Targets.cmake
  NAMESPACE ${DATAMODEL_NAME}::
  DESTINATION lib/cmake/${DATAMODEL_NAME}
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${DATAMODEL_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${DATAMODEL_NAME}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${DATAMODEL_NAME}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${DATAMODEL_NAME}Config.cmake"
  DESTINATION lib/cmake/${DATAMODEL_NAME}
)
