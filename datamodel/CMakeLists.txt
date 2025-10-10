# CMakeLists.txt for DELPHI EDM4hep custom data model
# This file handles the generation of C++ classes from YAML schema

cmake_minimum_required(VERSION 3.16)

# Find required packages for data model generation
find_package(podio REQUIRED)
find_package(EDM4HEP REQUIRED)

set(DATAMODEL_OUTPUT_DIR "${CMAKE_BINARY_DIR}/datamodel")

# Generate the data model classes from YAML into build directory
podio_generate_datamodel(edm4delphi 
  ${CMAKE_CURRENT_SOURCE_DIR}/edm4delphi.yaml 
  headers sources
  IO_BACKEND_HANDLERS ROOT
  UPSTREAM_EDM edm4hep:${EDM4HEP_DATA_DIR}/edm4hep.yaml
  OUTPUT_FOLDER ${DATAMODEL_OUTPUT_DIR}
)

podio_add_datamodel_core_lib(edm4delphi "${headers}" "${sources}")
target_link_libraries(edm4delphi PUBLIC EDM4HEP::edm4hep)

# Add include directories for generated headers
target_include_directories(edm4delphi 
  PUBLIC 
  $<BUILD_INTERFACE:${HEADERS_OUTPUT_DIR}>
  $<INSTALL_INTERFACE:include>
)

podio_add_root_io_dict(edm4delphiDict edm4delphi "${headers}" 
  ${CMAKE_BINARY_DIR}/datamodel/src/selection.xml
  OUTPUT_FOLDER ${DATAMODEL_OUTPUT_DIR}
)
