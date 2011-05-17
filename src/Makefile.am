AM_CPPFLAGS = \
	-DSCALIB_COMPILATION

lib_LTLIBRARIES = libsca.la

libsca_la_SOURCES =		\
	scaangle.c		\
	scacoordinates.c	\
	scaearth.c		\
	scajulianday.c		\
	scamisc.c		\
	scamoon.c		\
	scaplanetdata.c		\
	scastar.c		\
	scasun.c

scaincludedir=$(includedir)/sca
scainclude_HEADERS = 		\
	scaangle.h		\
	scacoordinates.h	\
	scaearth.h		\
	scajulianday.h		\
	scalib.h		\
	scamacros.h		\
	scamisc.h		\
	scamoon.h		\
	scaplanetdata.h		\
	scastar.h		\
	scasun.h

libsca_la_LIBADD=@SCA_LIBS@
libsca_la_CFLAGS=@SCA_CFLAGS@

