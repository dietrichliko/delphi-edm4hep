# DELPHI EDM4Hep
#
# CMakeLists.txt
#
# Create DELPHI EDM4Hep Produucer 

#
# Dietrich Liko <Dietrich.Liko@oeaw.ac.at>

cmake_minimum_required(VERSION 3.26)

project(DELPHI-EDM4Hep VERSION 0.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(DELPHI REQUIRED)

# fetch argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# fetch yaml-cpp
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

add_executable(delphi-edm4hep 
    src/main.cxx
    src/EDM4HepWriter.cxx
)

# version header
add_custom_target(version ALL
    COMMAND ${CMAKE_COMMAND} 
      -D PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}
      -D SRC=${CMAKE_SOURCE_DIR}/include/delphi-nanoaod_version.hpp.in
      -D DST=${CMAKE_BINARY_DIR}/include/delphi-nanoaod_version.hpp 
      -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake
    COMMENT "Creating version header"
    VERBATIM
    )

add_dependencies(delphi-edm4hep version)

