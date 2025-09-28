execute_process(
  COMMAND git describe --tags --dirty --match "v*" --always
  OUTPUT_VARIABLE VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

configure_file(${SRC} ${DST} @ONLY)
