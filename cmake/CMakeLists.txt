# config file support for find_package(SCA). This needs to
# deal with two environments: (1) finding the build tree and (2)
# finding the install tree. sca-config.cmake detects which
# situation it is handing by looking at @SCA_ROOT_DIR@. If
# this is an absolute path, it's in the build tree; otherwise,
# it's in the install tree (note that the whole install tree
# can be relocated).

# sca-config.cmake for the build tree.
set (SCA_ROOT_DIR ${PROJECT_BINARY_DIR})
set (SCA_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src)
configure_file (sca-config.cmake.in ${PROJECT_BINARY_DIR}/sca-config.cmake @ONLY)
configure_file (sca-config-version.cmake.in ${PROJECT_BINARY_DIR}/sca-config-version.cmake @ONLY)
export (TARGETS sca scastatic FILE ${PROJECT_BINARY_DIR}/sca-targets.cmake)

# sca-config.cmake for the install tree. It's installed in
# ${INSTALL_CMAKE_DIR} and @SCA_ROOT_DIR@ is the relative
# path to the root from there (note that the whole install tree can
# be relocated).
set (INSTALL_CMAKE_DIR cmake)
set (SCA_ROOT_DIR ..)

# @SCA_INCLUDE_DIRS@ is not used in the install tree; reset
# it to prevent the source and build paths appearing in the installed
# config files.
set (SCA_INCLUDE_DIRS IGNORE)
configure_file (sca-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/sca-config.cmake @ONLY)
configure_file (sca-config-version.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/sca-config-version.cmake @ONLY)
install (FILES
	${CMAKE_CURRENT_BINARY_DIR}/sca-config.cmake
	${CMAKE_CURRENT_BINARY_DIR}/sca-config-version.cmake
	DESTINATION ${INSTALL_CMAKE_DIR}
	COMPONENT Core
)

# Make information about the cmake targets available.
install (EXPORT sca-targets
	FILE sca-targets.cmake
	DESTINATION ${INSTALL_CMAKE_DIR}
	COMPONENT Core
)
