include_directories(${CMAKE_BINARY_DIR}
		    ${PROJECT_SOURCE_DIR}
		    ${PROJECT_SOURCE_DIR}/src
		    ${PROJECT_SOURCE_DIR}/config/win32
)

set(SCALIB_PUBLIC_HDRS
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

set(SCALIB_PRIVATE_HDRS
	${PROJECT_SOURCE_DIR}/config/win32/config.h
	${PROJECT_SOURCE_DIR}/config/win32/scalib.def
)

set(SCALIB_SRCS
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

add_library(sca SHARED ${SCALIB_SRCS} ${SCALIB_PUBLIC_HDRS} ${SCALIB_PRIVATE_HDRS})
add_library(scastatic STATIC ${SCALIB_SRCS} ${SCALIB_PUBLIC_HDRS} ${SCALIB_PRIVATE_HDRS})
add_definitions(-DSCALIB_COMPILATION)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set_target_properties(sca PROPERTIES SOVERSION ${SCA_VERSION})
set_target_properties(scastatic PROPERTIES SOVERSION ${SCA_VERSION})

install(TARGETS sca scastatic EXPORT sca-targets
	DESTINATION bin
    	RUNTIME DESTINATION bin
	COMPONENT Core
)

install(TARGETS sca scastatic
	DESTINATION lib
    	ARCHIVE DESTINATION lib
	COMPONENT Core
)
install(TARGETS sca scastatic
	DESTINATION lib
    	LIBRARY DESTINATION lib
	COMPONENT Core
)

install(FILES ${SCALIB_PUBLIC_HDRS}
	DESTINATION include
	COMPONENT Core
)

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)

install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} 
	DESTINATION bin
	COMPONENT Core
)
