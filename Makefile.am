SUBDIRS = src

uninstall-local:
	rm -rf $(DESTDIR)$(includedir)/sca

EXTRA_DIST =	\
	sca.pc.in				\
	Doxyfile				\
	CMakeLists.txt				\
	config/win32/config.h			\
	config/win32/scalib.def			\
	cmake\CMakeLists.txt			\
	cmake\sca-config-version.cmake.in	\
	cmake\sca-config.cmake.in		\
	cmake\FindSCA.cmake

BUILT_SOURCES = stamp-pc-h
stamp-pc-h: config.status
	echo timestamp > stamp-pc-h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sca.pc

$(pkgconfig_DATA): config.status

DISTCLEANFILES = stamp-pc-h
