set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Installation directory for headers")

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

set_target_properties(sca PROPERTIES SOVERSION ${VERSION})
set_target_properties(scastatic PROPERTIES SOVERSION ${VERSION})

install(TARGETS sca scastatic
    	RUNTIME DESTINATION ${INSTALL_BIN_DIR}
    	ARCHIVE DESTINATION ${INSTALL_LIB_DIR
    	LIBRARY DESTINATION ${INSTALL_LIB_DIR}
)
install(FILES ${SCALIB_PUBLIC_HDRS} DESTINATION ${INSTALL_INC_DIR})