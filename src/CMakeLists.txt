# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: CMake for the conversion project

# EDM4hep conversion program - include edm4hep_writer.cpp and analysis.cpp
add_executable(delphi_edm4hep_writer main_edm4hep_writer.cpp edm4hep_writer.cpp phdst/analysis.cpp phdst/zebra_pointer.cpp phdst/zebra_pointer.f)

# Set include directories for EDM4hep program
target_include_directories(delphi_edm4hep_writer
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${EDM4HEP_INCLUDE_DIRS}
)

# Configure spdlog for single-threaded mode
target_compile_definitions(delphi_edm4hep_writer 
    PRIVATE 
    SPDLOG_NO_THREAD_ID
    SPDLOG_NO_TLS
)

# Link DELPHI and CERN libraries for EDM4hep program
target_link_dellibs(delphi_edm4hep_writer PRIVATE phdst dstana pxdst vfclap vdclap ufield bsaurus)
target_link_cernlibs(delphi_edm4hep_writer PRIVATE genlib packlib jetset74)

# Link modern C++ libraries for EDM4hep program
target_link_libraries(delphi_edm4hep_writer 
    PRIVATE 
    argparse::argparse 
    spdlog::spdlog
    tomlplusplus::tomlplusplus
    EDM4HEP::edm4hep 
    podio::podioRootIO
    edm4delphi
    edm4delphiDict
)