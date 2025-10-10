# Copyright (c) 2025 Members of the DELPHI collaboration
# SPDX-License-Identifier: GPL-3.0-or-later
# Project: DELPHI-EDM4hep
#
# Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
# Description: Doxygen documentation configuration

# Function to setup Doxygen documentation
function(setup_doxygen)
    # Build options
    option(BUILD_DOCS "Build documentation with Doxygen" ON)
    
    # Find Doxygen for documentation generation
    if(BUILD_DOCS)
        find_package(Doxygen)
        if(DOXYGEN_FOUND)
            # Set Doxygen configuration variables
            set(DOXYGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src" PARENT_SCOPE)
            set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs" PARENT_SCOPE)
            set(DOXYGEN_INDEX_FILE "${CMAKE_BINARY_DIR}/docs/html/index.html")
            
            # Create Doxyfile from template
            configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
            
            # Create output directory
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
            
            # Add custom target for generating documentation
            add_custom_target(docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
            
            # Make docs target depend on all source files
            file(GLOB_RECURSE DOXYGEN_SOURCES 
                 "${CMAKE_SOURCE_DIR}/include/*.hpp"
                 "${CMAKE_SOURCE_DIR}/src/*.cpp"
                 "${CMAKE_SOURCE_DIR}/src/*.hpp")
            
            add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                               DEPENDS ${DOXYGEN_SOURCES}
                               COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
                               WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                               MAIN_DEPENDENCY ${CMAKE_BINARY_DIR}/Doxyfile
                               COMMENT "Generating docs")
            
            # Create a target that builds the docs (not by default)
            add_custom_target(doxygen DEPENDS ${DOXYGEN_INDEX_FILE})
            
            # Install documentation
            install(DIRECTORY ${CMAKE_BINARY_DIR}/docs/html
                    DESTINATION share/doc/delphi-edm4hep
                    OPTIONAL)
            
            message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE}")
            message(STATUS "Documentation will be generated in: ${CMAKE_BINARY_DIR}/docs")
            message(STATUS "Build documentation with: make docs or make doxygen")
        else()
            message(WARNING "Doxygen not found - documentation will not be generated")
            message(STATUS "Install doxygen package to enable documentation generation")
        endif()
    else()
        message(STATUS "Documentation generation disabled (BUILD_DOCS=OFF)")
    endif()
endfunction()
