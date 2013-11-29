set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (OUTPUT_DIR ${CMAKE_BINARY_DIR})

include (CheckPrototypeExists)
include_directories (${CMAKE_BINARY_DIR}
		    ${PROJECT_SOURCE_DIR}
		    ${PROJECT_SOURCE_DIR}/src
)

configure_file (
	"${PROJECT_SOURCE_DIR}/src/scalib.def.in"
	"${CMAKE_BINARY_DIR}/scalib.def"
)

set (SCALIB_PUBLIC_HDRS
	scaangle.h
	scacoordinates.h
	scaearth.h
	scajulianday.h
	scalib.h
	scamacros.h
	scamisc.h
	scamoon.h
	scaplanetdata.h
	scastar.h
	scasun.h
)

if (WIN32)
	set (SCALIB_PRIVATE_HDRS ${CMAKE_BINARY_DIR}/scalib.def)
endif()

set (SCALIB_SRCS
	scaangle.c
	scacoordinates.c
	scaearth.c
	scajulianday.c
	scamisc.c
	scamoon.c
	scaplanetdata.c
	scastar.c
	scasun.c
)

add_library (sca SHARED ${SCALIB_SRCS} ${SCALIB_PUBLIC_HDRS} ${SCALIB_PRIVATE_HDRS})
add_library (scastatic STATIC ${SCALIB_SRCS} ${SCALIB_PUBLIC_HDRS} ${SCALIB_PRIVATE_HDRS})
add_definitions (-DSCALIB_COMPILATION)

if (MSVC)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)
endif()

check_prototype_exists (trunc "math.h" HAVE_TRUNC_DECL)
if (HAVE_TRUNC_DECL)
	add_definitions (-DHAVE_TRUNC_DECL)
endif()

if (NOT WIN32)
	add_definitions (-D_REENTRANT
			 -D_PTHREADS
			 -D_POSIX4_DRAFT_SOURCE
			 -D_POSIX4A_DRAFT10_SOURCE
			 -U_OSF_SOURCE
			 -D_THREAD_SAFE
	)

	target_link_libraries (sca m)
	target_link_libraries (scastatic m)
endif()

set_target_properties (sca PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties (sca PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties (scastatic PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties (sca PROPERTIES SOVERSION ${SCA_VERSION})
set_target_properties (scastatic PROPERTIES SOVERSION ${SCA_VERSION})

if (WIN32)
	install (TARGETS sca scastatic
		DESTINATION lib
	    	RUNTIME DESTINATION lib
		COMPONENT Core
	)

	if (NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
		set (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS TRUE)
	endif()

	set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
	include(InstallRequiredSystemLibraries)
	
	install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} 
		DESTINATION lib
		COMPONENT Core
	)
endif()

install (TARGETS sca scastatic EXPORT sca-targets
	DESTINATION lib
    	LIBRARY DESTINATION lib
	COMPONENT Core
)
install (TARGETS sca scastatic
	DESTINATION lib
    	ARCHIVE DESTINATION lib
	COMPONENT Core
)
install(FILES ${SCALIB_PUBLIC_HDRS}
	DESTINATION include/SCA
	COMPONENT Core
)
