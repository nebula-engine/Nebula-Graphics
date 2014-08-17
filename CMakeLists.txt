CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_gfx)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

FIND_PACKAGE(glfw)

#FIND_PACKAGE(Galaxy COMPONENTS
#	std
#	log
#	console
#	REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
	core
	REQUIRED)

#INCLUDE_DIRECTORIES("/usr/include/python2.7")
include_directories("/usr/include/freetype2")
#include_directories("./glm")

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

# custom include extensions

SET(libs
	${nebula_LIBRARIES}
	#${Galaxy_LIBRARIES}
	${Boost_LIBRARIES}
	${glfw_LIBRARIES}
	)

INCLUDE(cmh_library)

add_subdirectory(test)


