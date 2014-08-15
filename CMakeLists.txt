CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(nebula_gfx)

FIND_PACKAGE(CMakeHelper)
FIND_PACKAGE(glfw)

FIND_PACKAGE(Galaxy COMPONENTS
	std
	log
	console
	REQUIRED)

FIND_PACKAGE(Nebula COMPONENTS
	core
	REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

INCLUDE_DIRECTORIES("/usr/include/python2.7")
include_directories("/usr/include/freetype2")
include_directories("./glm")

ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)


#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_STATIC_RUNTIME OFF)
#add_definitions(-DBOOST_ALL_DYN_LINK)

#FIND_PACKAGE(Boost 1.55 COMPONENTS
#	log
#	REQUIRED)

SET(libs ${libs}
	${PROJECT_NAME}
	${Nebula_LIBRARIES}
	${Galaxy_LIBRARIES}
	${Boost_LIBRARIES}
	${glfw_LIBRARIES}
	)

cmh_static_library()

add_subdirectory(test)


