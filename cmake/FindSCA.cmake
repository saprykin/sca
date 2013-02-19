# Look for SCA
find_library(SCA_LIBRARIES sca PATHS ${CMAKE_INSTALL_PREFIX}/../sca/lib)

if(SCA_LIBRARIES)
	get_filename_component(SCA_LIBRARY_DIRS ${SCA_LIBRARIES} PATH)
	get_filename_component(SCA_ROOT_DIR ${SCA_LIBRARY_DIRS} PATH)
	set(SCA_INCLUDE_DIRS ${SCA_ROOT_DIR}/src)
	unset(SCA_ROOT_DIR)
	if(NOT EXISTS ${SCA_INCLUDE_DIRS}/scalib.h)
		unset(SCA_INCLUDE_DIRS)
		unset(SCA_LIBRARIES)
		unset(SCA_LIBRARY_DIRS)
	endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SCA DEFAULT_MSG SCA_LIBRARY_DIRS SCA_LIBRARIES SCA_INCLUDE_DIRS)
mark_as_advanced(SCA_LIBRARY_DIRS SCA_LIBRARIES SCA_INCLUDE_DIRS)
