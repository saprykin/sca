SUBDIRS = src
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST =			\
	sca.pc.in		\
	Doxyfile

BUILT_SOURCES = stamp-pc-h
stamp-pc-h: config.status
	echo timestamp > stamp-pc-h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sca.pc

$(pkgconfig_DATA): config.status

DISTCLEANFILES = stamp-pc-h

