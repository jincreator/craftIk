#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([craftIk], [20121019], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign])
LT_INIT
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CC_STDC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

# Checks for system.
AC_CANONICAL_HOST

# Compiler Option
AS_CASE([$host_os],
	[linux*],[CC=gcc],
	[*bsd*],[CC=clang],
	[darwin*],[CC=clang],
	[*],[]
)
CFLAGS="$CFLAGS -std=c11"

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
#AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
                 include/Makefile
		 src/Makefile])
AC_OUTPUT
