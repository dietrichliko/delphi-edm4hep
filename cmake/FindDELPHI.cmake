# Modern DELPHI Analysis Examples
#
# FindDELPHI.cmake
#
# Some common utility functions
#
# Dietrich Liko <Dietrich.Liko@oeaw.ac.at>

cmake_minimum_required(VERSION 3.26)

project(DELPHI VERSION 0.1 LANGUAGES Fortran CXX)

# Wrapper for nypatchy, the DELPHI source code manager
# 
# Dependencies to CAR files can be added to the command
#
# ypatchy(<Fortran File> <CRA File> [<CAR Files> ...)
#
# Example
#
#    configure_file(example01.cra.in example01.cra)
#    ypatchy(example01.f example01.cra)
#
function(ypatchy FOUT CRA)

    add_custom_command(
        OUTPUT ${FOUT}
        MAIN_DEPENDENCY ${CRA}
        DEPENDS ${ARGN}
        COMMAND nypatchy - ${FOUT} ${CRA} nypatchy.ylog .go
        COMMENT "Running nypatchy on ${CRA}"
        VERBATIM
        )

endfunction()

# Wrapper for the cernlib command that simplifies link options
# Usage: target_link_cernlibs(<TARGET> [PRIVATE|PUBLIC|INTERFACE] <cernlib_args>...)
function(target_link_cernlibs TARGET)

    # Parse arguments to extract visibility
    set(VISIBILITY_OPTIONS PRIVATE PUBLIC INTERFACE)
    set(VISIBILITY "PRIVATE")  # Default visibility
    set(CERNLIB_ARGS ${ARGN})
    
    # Check if first argument is a visibility specifier
    list(GET ARGN 0 FIRST_ARG)
    if(FIRST_ARG IN_LIST VISIBILITY_OPTIONS)
        set(VISIBILITY ${FIRST_ARG})
        list(REMOVE_AT CERNLIB_ARGS 0)  # Remove visibility from cernlib args
    endif()

    execute_process(
        COMMAND cernlib ${CERNLIB_ARGS}
        OUTPUT_VARIABLE CERNLIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    target_link_libraries(${TARGET} ${VISIBILITY} ${CERNLIBS})

endfunction()

# Wrapper for the dellib command that simplifies link options
# Usage: target_link_dellibs(<TARGET> [PRIVATE|PUBLIC|INTERFACE] <dellib_args>...)
function(target_link_dellibs TARGET)

    # Parse arguments to extract visibility
    set(VISIBILITY_OPTIONS PRIVATE PUBLIC INTERFACE)
    set(VISIBILITY "PRIVATE")  # Default visibility
    set(DELLIB_ARGS ${ARGN})
    
    # Check if first argument is a visibility specifier
    list(GET ARGN 0 FIRST_ARG)
    if(FIRST_ARG IN_LIST VISIBILITY_OPTIONS)
        set(VISIBILITY ${FIRST_ARG})
        list(REMOVE_AT DELLIB_ARGS 0)  # Remove visibility from dellib args
    endif()

    execute_process(
        COMMAND dellib ${DELLIB_ARGS}
        OUTPUT_VARIABLE DELLIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    target_link_libraries(${TARGET} ${VISIBILITY} ${DELLIBS})

endfunction()