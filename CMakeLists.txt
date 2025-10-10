# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: CMake for the whole project

cmake_minimum_required(VERSION 3.26)

project(DELPHI-EDM4HEP VERSION 0.1 LANGUAGES CXX Fortran)
set (CMAKE_CXX_STANDARD 17)

add_compile_options(-ftemplate-depth=512)

# Global linking to gfortran for Fortran/C++ interoperability
link_libraries(gfortran)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Setup git version information
include(GitVersion)
setup_git_version()

find_package(DELPHI REQUIRED)
find_package(EDM4HEP REQUIRED)
find_package(podio REQUIRED)

# Add the custom data model subdirectory
add_subdirectory(datamodel)

# Setup Doxygen documentation
include(Doxygen)
setup_doxygen()

# fetch argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# fetch spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
)
FetchContent_MakeAvailable(spdlog)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

add_subdirectory(src)
