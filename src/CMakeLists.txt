# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: CMake for the conversion project

# Main analysis program - include Analysis.cpp directly
add_executable(delphi_phdst main_phdst.cpp phdst/Analysis.cpp)

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

# Link DELPHI and CERN libraries first (these don't use visibility specifiers)
target_link_dellibs(delphi_phdst phdstxx)
target_link_cernlibs(delphi_phdst packlib genlib)

# Link modern C++ libraries with visibility specifiers
target_link_libraries(delphi_phdst 
    PRIVATE 
    argparse::argparse 
    spdlog::spdlog
)

# EDM4hep conversion program - include EDM4hepWriter.cpp and Analysis.cpp
add_executable(delphi_edm4hep_writer main_edm4hep.cpp EDM4hepWriter.cpp phdst/Analysis.cpp)

# Set include directories for EDM4hep program
target_include_directories(delphi_edm4hep_writer 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${EDM4HEP_INCLUDE_DIRS}
)

# Configure spdlog for single-threaded mode
target_compile_definitions(delphi_edm4hep_writer 
    PRIVATE 
    SPDLOG_NO_THREAD_ID
    SPDLOG_NO_TLS
)

# Link DELPHI and CERN libraries for EDM4hep program
target_link_dellibs(delphi_edm4hep_writer phdstxx)
target_link_cernlibs(delphi_edm4hep_writer packlib genlib)

# Link modern C++ libraries for EDM4hep program
target_link_libraries(delphi_edm4hep_writer 
    PRIVATE 
    argparse::argparse 
    spdlog::spdlog
    EDM4HEP::edm4hep 
    podio::podioRootIO
    delphi_edm4hep
)

# The data model library will be automatically built due to the target_link_libraries dependency