CMAKE_MINIMUM_REQUIRED(VERSION 2.0)
PROJECT(libbasehangul)

INCLUDE (CheckIncludeFiles)

CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h)

SET(LIB_BASE_HANGUL_SRCS
    src/basehangul.c)

SET(LIB_BASE_HANGUL_EXT_HDRS
    include/basehangul.h
    include/config.h
    include/type.h)

SET(LIB_BASE_HANGUL_INT_HDRS
    src/digit_set.h)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(basehangul
            ${LIB_BASE_HANGUL_SRCS}
            ${LIB_BASE_HANGUL_EXT_HDRS}
            ${LIB_BASE_HANGUL_INT_HDRS})
