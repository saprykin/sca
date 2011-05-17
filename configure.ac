AC_PREREQ(2.54)

AC_INIT([sca], [0.0.1], [xelfium@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_MAINTAINER_MODE
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_CONFIG_HEADER([config.h])

dnl Enable silent build when available (Automake 1.11)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

dnl Check programs and stuff
AC_PROG_CC
AM_PROG_CC_STDC
AM_PROG_CC_C_O
AC_PROG_INSTALL

AM_DISABLE_STATIC
AM_PROG_LIBTOOL

dnl Check header files
AC_HEADER_STDC
dnl AC_CHECK_HEADERS([stdio.h fcntl.h sys/socket.h netinet/in.h errno.h arpa/inet.h])

SCA_CFLAGS="-D_REENTRANT -D_PTHREADS -D_POSIX4_DRAFT_SOURCE -D_POSIX4A_DRAFT10_SOURCE -U_OSF_SOURCE -D_THREAD_SAFE"
SCA_LIBS="-lm"

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

AC_CONFIG_FILES([Makefile src/Makefile sca.pc])
AC_OUTPUT

