set(LIBNAME "residc")
set(OUTDIR bin)

set(reSIDc_SRCS
    ../deps/envelope.cc
    ../deps/extfilt.cc
    ../deps/filter.cc
    ../deps/pot.cc
    ../deps/sid.cc
    ../deps/version.cc
    ../deps/voice.cc
    ../deps/wave.cc
    ../deps/wave6581__ST.cc
    ../deps/wave6581_P_T.cc
    ../deps/wave6581_PS_.cc
    ../deps/wave6581_PST.cc
    ../deps/wave8580__ST.cc
    ../deps/wave8580_P_T.cc
    ../deps/wave8580_PS_.cc
    ../deps/wave8580_PST.cc
    residc.cpp
)

set(reSIDc_HDRS
    ../deps/envelope.h
    ../deps/extfilt.h
    ../deps/filter.h
    ../deps/pot.h
    ../deps/sid.h
    ../deps/siddefs.h
    ../deps/spline.h
    ../deps/voice.h
    ../deps/wave.h
    residc.h
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/bin)

add_library(reSIDc_shared SHARED
    ${reSIDc_HDRS}
    ${reSIDc_SRCS}
)

set_target_properties(reSIDc_shared PROPERTIES
    OUTPUT_NAME ${LIBNAME}
    CLEAN_DIRECT_OUTPUT 1
    VERSION "1.0"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTDIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTDIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTDIR}/bin"
)

set_target_properties(reSIDc_shared PROPERTIES LINKER_LANGUAGE CPP)
