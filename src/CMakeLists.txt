# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: CMake for the conversion project

# PHDST Analysis library
add_library(phdst_analysis phdst/Analysis.cpp)

# Set include directories for the library
target_include_directories(phdst_analysis 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

# Main analysis program
add_executable(delphi_phdst main_phdst.cpp)

# Link required libraries
target_link_libraries(delphi_phdst 
    PRIVATE 
    argparse::argparse 
    spdlog::spdlog
    phdst_analysis
)

# Set include directories
target_include_directories(delphi_phdst 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# Configure spdlog for single-threaded mode
target_compile_definitions(delphi_phdst 
    PRIVATE 
    SPDLOG_NO_THREAD_ID
    SPDLOG_NO_TLS
)