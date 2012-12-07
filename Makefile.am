SUBDIRS = src

BUILT_SOURCES = stamp-pc-h
stamp-pc-h: config.status
	echo timestamp > stamp-pc-h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sca.pc

$(pkgconfig_DATA): config.status

DISTCLEANFILES = stamp-pc-h
