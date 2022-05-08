# gensrc.cmake.in
# Generate source files with awk, based upon the automake logic.

# Copyright (C) 2016 Glenn Randers-Pehrson
# Written by Roger Leigh, 2016

# This code is released under the libpng license.
# For conditions of distribution and use, see the disclaimer
# and license in png.h

# Variables substituted from CMakeLists.txt
set(SRCDIR "D:/VisualStudio/SDL2/SDL2-GameDevCMake/SDL2-Minesweeper/external/sdl_image/external/libpng")
set(BINDIR "D:/VisualStudio/SDL2/SDL2-GameDevCMake/SDL2-Minesweeper/out/build/external/sdl_image/external/libpng")

set(AWK "AWK-NOTFOUND")
set(DFA_XTRA "")
set(PNG_PREFIX "")
set(PNGLIB_VERSION "1.6.37")

if("${OUTPUT}" STREQUAL "scripts/pnglibconf.c")
  # Generate scripts/pnglibconf.c

  file(REMOVE "${BINDIR}/pnglibconf.tf6" "${BINDIR}/pnglibconf.tf7")

  execute_process(COMMAND "${CMAKE_COMMAND}" -E echo "com ${PNGLIB_VERSION} STANDARD API DEFINITION"
                  COMMAND "${AWK}" -f "${SRCDIR}/scripts/options.awk"
                          "out=pnglibconf.tf6" "logunsupported=1" "version=search"
                          "${SRCDIR}/pngconf.h" "-"
                          "${SRCDIR}/scripts/pnglibconf.dfa"
                  WORKING_DIRECTORY "${BINDIR}"
                  RESULT_VARIABLE AWK_FAIL)
  if(AWK_FAIL)
    message(FATAL_ERROR "Failed to generate pnglibconf.tf6")
  endif()

  execute_process(COMMAND "${AWK}" -f "${SRCDIR}/scripts/options.awk"
                  "out=pnglibconf.tf7" "pnglibconf.tf6"
                  WORKING_DIRECTORY "${BINDIR}"
                  RESULT_VARIABLE AWK_FAIL)
  if(AWK_FAIL)
    message(FATAL_ERROR "Failed to generate pnglibconf.tf7")
  endif()

  file(REMOVE "pnglibconf.tf6")
  file(MAKE_DIRECTORY "${BINDIR}/scripts")
  file(RENAME "pnglibconf.tf7" "${BINDIR}/scripts/pnglibconf.c")

elseif ("${OUTPUT}" STREQUAL "pnglibconf.c")
  # Generate pnglibconf.c

  file(REMOVE "${BINDIR}/pnglibconf.tf4" "${BINDIR}/pnglibconf.tf5")

  execute_process(COMMAND "${AWK}" -f "${SRCDIR}/scripts/options.awk"
                  out=pnglibconf.tf4 version=search
                  ${SRCDIR}/pngconf.h ${SRCDIR}/scripts/pnglibconf.dfa
                  ${SRCDIR}/pngusr.dfa ${DFA_XTRA}
                  WORKING_DIRECTORY "${BINDIR}"
                  RESULT_VARIABLE AWK_FAIL)
  if(AWK_FAIL)
    message(FATAL_ERROR "Failed to generate pnglibconf.tf4")
  endif()

  execute_process(COMMAND "${AWK}" -f "${SRCDIR}/scripts/options.awk"
                  out=pnglibconf.tf5 pnglibconf.tf4
                  WORKING_DIRECTORY "${BINDIR}"
                  RESULT_VARIABLE AWK_FAIL)
  if(AWK_FAIL)
    message(FATAL_ERROR "Failed to generate pnglibconf.tf5")
  endif()

  file(REMOVE "pnglibconf.tf4")
  file(MAKE_DIRECTORY "${BINDIR}/scripts")
  file(RENAME "pnglibconf.tf5" "${BINDIR}/pnglibconf.c")

elseif ("${OUTPUT}" STREQUAL "pnglibconf.h")
  # Generate pnglibconf.h

  file(REMOVE "${BINDIR}/${OUTPUT}")
  if(PNG_PREFIX)
    file(REMOVE "pnglibconf.tf8")

    execute_process(COMMAND "${AWK}" "s==0 && NR>1{print prev}
                             s==0{prev=\$0}
                             s==1{print \"#define\", \$1, \"${PNG_PREFIX}\" \$1}
                             s==2{print \"#define ${PNG_PREFIX}png_\" \$1, \"PNG_\" \$1}
                             END{print prev}" s=0 pnglibconf.out s=1 "${BINDIR}/scripts/prefix.out"
                             s=2 "${SRCDIR}/scripts/macro.lst"
                    OUTPUT_FILE pnglibconf.tf8
                    RESULT_VARIABLE AWK_FAIL)
    if(AWK_FAIL)
      message(FATAL_ERROR "Failed to generate pnglibconf.tf8")
    endif()

    file(RENAME "pnglibconf.tf8" "${BINDIR}/${OUTPUT}")
  else()
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy "${BINDIR}/pnglibconf.out"
                                                       "${BINDIR}/${OUTPUT}"
                    RESULT_VARIABLE COPY_FAIL)
    if(COPY_FAIL)
      message(FATAL_ERROR "Failed to create pnglibconf.h")
    endif()
  endif()

elseif ("${OUTPUT}" STREQUAL "pngprefix.h")
  # Generate pngprefix.h

  file(REMOVE "${BINDIR}/${OUTPUT}")

  if(PNG_PREFIX)
    file(REMOVE "pngprefix.tf1")

    execute_process(COMMAND "${AWK}"
                            "{print \"#define\", \$1, \"${PNG_PREFIX}\" \$1}"
                            "${BINDIR}/scripts/intprefix.out"
                    OUTPUT_FILE "pngprefix.tf1"
                    RESULT_VARIABLE AWK_FAIL)
    if(AWK_FAIL)
      message(FATAL_ERROR "Failed to generate pngprefix.tf1")
    endif()

    file(RENAME "pngprefix.tf1" "${BINDIR}/${OUTPUT}")
  else()
    file(WRITE "${BINDIR}/${OUTPUT}" "/* No libpng symbol prefix configured. */")
  endif()

elseif("${OUTPUT}" STREQUAL "scripts/pnglibconf.h.prebuilt")
  # Generate scripts/pnglibconf.h.prebuilt (fails build)

  message(STATUS "Attempting to build scripts/pnglibconf.h.prebuilt")
  message(STATUS "This is a machine generated file, but if you want to make")
  message(STATUS "a new one simply build the 'genfiles' target, and copy")
  message(STATUS "scripts/pnglibconf.out to scripts/pnglibconf.h.prebuilt")
  message(STATUS "AND set PNG_ZLIB_VERNUM to 0 (you MUST do this)")
  message(FATAL_ERROR "Stopping build")

else()
  message(FATAL_ERROR "Unsupported output: ${OUTPUT}")
endif()
