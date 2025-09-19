ypatchy(skelana.f ${CMAKE_CURRENT_SOURCE_DIR}/skelana.cra)

add_executable(delphi-edm4hep 
    main.cpp
    EDM4HepWriter.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/skelana.f
)
target_include_directories(delphi-edm4hep PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(delphi-edm4hep argparse yaml-cpp spdlog)
target_compile_options(delphi-edm4hep PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-ftemplate-depth=50>) # argpase

target_link_dellibs(delphi-edm4hep skelana phdst dstana pxdst vfclap vdclap ufield bsaurus herlib trigger uhlib dstana)
target_link_cernlibs(delphi-edm4hep genlib packlib kernlib ariadne herwig jetset74)


target_link_libraries(delphi-edm4hep gfortran)

# version header
add_custom_target(version ALL
    COMMAND ${CMAKE_COMMAND} 
      -D PROJECT_SOURCE_DIR=${CMAKE_SOURCE_DIR}
      -D SRC=${CMAKE_SOURCE_DIR}/include/delphi-edm4hep_version.hpp.in
      -D DST=${CMAKE_BINARY_DIR}/include/delphi-edm4hep_version.hpp 
      -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake
    COMMENT "Creating version header"
    VERBATIM
    )

add_dependencies(delphi-edm4hep version)
target_include_directories(delphi-edm4hep PRIVATE ${CMAKE_BINARY_DIR}/include) # version header