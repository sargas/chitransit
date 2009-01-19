AC_PREREQ(2.63)
AC_INIT([chitransit],[0.707],[http://github.com/sargas/chitransit/tree/master])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR(src/main.c)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_SEARCH_LIBS([strerror],[cposix])
AC_PROG_CC
AC_PROG_CC_STDC
AC_HEADER_STDC

AC_CHECK_HEADERS([fcntl.h stdlib.h unistd.h])
AC_FUNC_FORK
AC_TYPE_PID_T

PKG_CHECK_MODULES(DEPENDENCIES, libglade-2.0 libcurl)

AC_SUBST(DEPENDENCIES)

AC_CONFIG_FILES([
Makefile
src/Makefile
data/Makefile
])
AC_OUTPUT
