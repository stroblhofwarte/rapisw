cmake_minimum_required(VERSION 2.4.7)
PROJECT(indi_rapisw CXX C)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules/")

include(GNUInstallDirs)

set (GENERIC_VERSION_MAJOR 0)
set (GENERIC_VERSION_MINOR 1)

find_package(Threads REQUIRED)
find_package(INDI REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/indi_rapisw.xml.cmake ${CMAKE_CURRENT_BINARY_DIR}/indi_rapisw.xml )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${INDI_INCLUDE_DIR})

include(CMakeCommon)

set(GPIO_LIBRARIES "libgpiod.so")

############# INDI PICAMERA ###############
set(indirapisw_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/basefocuser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/rapisw.cpp
)

add_executable(indi_rapisw ${indirapisw_SRCS})

target_link_libraries(indi_rapisw ${INDI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} m)

install(TARGETS indi_rapisw RUNTIME DESTINATION bin)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/indi_rapisw.xml DESTINATION ${INDI_DATA_DIR})
