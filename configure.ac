AC_PREREQ(2.54)

dnl Making releases:
dnl   scalib_micro_version += 1;
dnl   scalib_interface_age += 1;
dnl   scalib_binary_age += 1;
dnl if any functions have been added, set scalib_interface_age to 0;
dnl if backwards compatibility has been broken,
dnl set scalib_binary_age _AND_ scalib_interface_age to 0.
m4_define([scalib_major_version], [0])
m4_define([scalib_minor_version], [0])
m4_define([scalib_micro_version], [1])
m4_define([scalib_interface_age], [0])
m4_define([scalib_binary_age], [m4_eval(100 * scalib_minor_version + scalib_micro_version)])
m4_define([scalib_version], [scalib_major_version.scalib_minor_version.scalib_micro_version])

dnl Libtool version related macros
m4_define([scalib_lt_release], [scalib_major_version.scalib_minor_version])
m4_define([scalib_lt_current],
          [m4_eval(100 * scalib_minor_version + scalib_micro_version - scalib_interface_age)])
m4_define([scalib_lt_revision], [scalib_interface_age])
m4_define([scalib_lt_age], [m4_eval(scalib_binary_age - scalib_interface_age)])
m4_define([scalib_lt_current_minus_age], [m4_eval(scalib_lt_current - scalib_lt_age)])

AC_INIT([sca], [scalib_version], [xelfium@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

dnl Enable silent build when available (Automake 1.11)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_SRCDIR([src/scalib.h])
AC_CONFIG_HEADERS([config.h])

AM_MAINTAINER_MODE

SCALIB_MAJOR_VERSION=scalib_major_version
SCALIB_MINOR_VERSION=scalib_minor_version
SCALIB_MICRO_VERSION=scalib_micro_version
SCALIB_INTERFACE_AGE=scalib_interface_age
SCALIB_BINARY_AGE=scalib_binary_age
SCALIB_VERSION=scalib_version

AC_SUBST(SCALIB_MAJOR_VERSION)
AC_SUBST(SCALIB_MINOR_VERSION)
AC_SUBST(SCALIB_MICRO_VERSION)
AC_SUBST(SCALIB_VERSION)
AC_SUBST(SCALIB_INTERFACE_AGE)
AC_SUBST(SCALIB_BINARY_AGE)

AC_DEFINE(SCALIB_MAJOR_VERSION, [scalib_major_version], [Define to the SCALib major version])
AC_DEFINE(SCALIB_MINOR_VERSION, [scalib_minor_version], [Define to the SCALib minor version])
AC_DEFINE(SCALIB_MICRO_VERSION, [scalib_micro_version], [Define to the SCALib micro version])
AC_DEFINE(SCALIB_INTERFACE_AGE, [scalib_interface_age], [Define to the SCALib interface age])
AC_DEFINE(SCALIB_BINARY_AGE, [scalib_binary_age], [Define to the SCALib binary age])

dnl Libtool versioning
LT_RELEASE=scalib_lt_release
LT_CURRENT=scalib_lt_current
LT_REVISION=scalib_lt_revision
LT_AGE=scalib_lt_age
LT_CURRENT_MINUS_AGE=scalib_lt_current_minus_age
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
AC_SUBST(LT_CURRENT_MINUS_AGE)

dnl Check programs and stuff
AM_PROG_CC_C_O
AC_PROG_INSTALL

AM_DISABLE_STATIC
AM_PROG_AR
AM_PROG_LIBTOOL

dnl Check header files
AC_HEADER_STDC

SCA_CFLAGS="-D_REENTRANT -D_PTHREADS -D_POSIX4_DRAFT_SOURCE -D_POSIX4A_DRAFT10_SOURCE -U_OSF_SOURCE -D_THREAD_SAFE"
SCA_LIBS="-lm"

dnl Test whether trunc() is declared.
AC_CHECK_DECLS([trunc], , , [#include <math.h>])
if test "x$ac_cv_have_decl_trunc" = xyes; then
	AC_DEFINE(HAVE_TRUNC_DECL, 1, [define if system has trunc function declared])
fi

AC_SUBST(SCA_LIBS)
AC_SUBST(SCA_CFLAGS)

dnl Find pkg-config
AC_PATH_PROG(PKG_CONFIG, [pkg-config], [no])
if test "x$PKG_CONFIG" = xno; then
	AC_MSG_ERROR([*** pkg-config not found. See http://www.freedesktop.org/software/pkgconfig/])
fi

if $PKG_CONFIG --atleast-pkgconfig-version 0.16; then
	:
else
	AC_MSG_ERROR([*** pkg-config too old; version 0.16 or better required.])
fi

AC_CONFIG_FILES([Makefile src/Makefile sca.pc sca-uninstalled.pc Doxyfile Doxyfile.rus])
AC_OUTPUT

