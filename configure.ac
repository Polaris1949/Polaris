#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Polaris Library], [0.8.0], [BeiChen1949@gmail.com])
AC_CONFIG_SRCDIR([src/version.cc])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.15.1 no-define foreign no-dependencies no-dist -Wall -Wno-portability -Wno-override])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Libtool setup.
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIRS([.])
LT_INIT
AM_ENABLE_STATIC
AM_ENABLE_SHARED

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([memset pow sqrt])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT
