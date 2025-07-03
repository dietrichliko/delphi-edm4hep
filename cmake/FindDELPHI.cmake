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
function(target_link_cernlibs TARGET)

    execute_process(
        COMMAND cernlib ${ARGN}
        OUTPUT_VARIABLE CERNLIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    target_link_libraries(${TARGET} ${CERNLIBS})

endfunction()

# Wrapper for the dellib command that simplifies link options
function(target_link_dellibs TARGET)

    execute_process(
        COMMAND dellib ${ARGN}
        OUTPUT_VARIABLE DELLIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    target_link_libraries(${TARGET} ${DELLIBS})

endfunction()