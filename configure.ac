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
AC_CHECK_HEADERS([memory.h stddef.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_PID_T
#AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_FORK
#AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset stpcpy strstr])

AC_CONFIG_FILES([Library/CoreString/CoreStringTest/Makefile
                 Library/CoreString/Makefile
                 Library/Makefile
                 Library/ObjectSystem/Makefile
                 Library/ObjectSystem/ObjectSystemTest/Makefile
                 Library/Seatest/Makefile
                 Makefile
                 ProcessManager/Makefile
                 WatchFox/Makefile])
AC_OUTPUT
