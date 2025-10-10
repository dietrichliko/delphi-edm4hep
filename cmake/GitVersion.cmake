# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: Git version information configuration

# Function to setup git version information
function(setup_git_version)
    # Get git version information
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        
        execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=iso
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_DATE
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        
        message(STATUS "Git version: ${GIT_VERSION}")
        message(STATUS "Git commit: ${GIT_COMMIT_HASH}")
        message(STATUS "Git date: ${GIT_COMMIT_DATE}")
    else()
        set(GIT_VERSION "unknown")
        set(GIT_COMMIT_HASH "unknown")
        set(GIT_COMMIT_DATE "unknown")
        message(WARNING "Git not found - version information will be set to 'unknown'")
    endif()
    
    # Make variables available to parent scope
    set(GIT_VERSION ${GIT_VERSION} PARENT_SCOPE)
    set(GIT_COMMIT_HASH ${GIT_COMMIT_HASH} PARENT_SCOPE)
    set(GIT_COMMIT_DATE ${GIT_COMMIT_DATE} PARENT_SCOPE)
    
    # Configure version header file
    configure_file(
        "${CMAKE_SOURCE_DIR}/DELPHI_EDM4hepVersion.hpp.in"
        "${CMAKE_BINARY_DIR}/include/DELPHI_EDM4hepVersion.hpp"
        @ONLY
    )
    
    message(STATUS "Version header generated: ${CMAKE_BINARY_DIR}/include/version.hpp")
endfunction()
