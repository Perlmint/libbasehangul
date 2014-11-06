CMAKE_MINIMUM_REQUIRED(VERSION 2.0)
PROJECT(libbasehangul)

INCLUDE (CheckIncludeFiles)

CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h)

IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
ENDIF()

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

IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ext/gtest/libgtest.a OR
   EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ext/gtest/libgtest.dll)
    SET(BASE_HANGUL_TESTS
        test/test_example.cc)

    ADD_EXECUTABLE(basehangul_test
		   ${BASE_HANGUL_TESTS})

    FIND_LIBRARY(GTEST_LIB gtest
                 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/ext/gtest)
    FIND_LIBRARY(GTEST_MAIN_LIB gtest_main
                 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/ext/gtest)

    TARGET_INCLUDE_DIRECTORIES(basehangul_test
                               PRIVATE ext/gtest/include
			       PRIVATE src)

    TARGET_LINK_LIBRARIES(basehangul_test
                          basehangul
                          ${GTEST_LIB}
			  ${GTEST_MAIN_LIB})

    ENABLE_TESTING()

    ADD_TEST(NAME unit_test
             COMMAND basehangul_test)
ENDIF()
