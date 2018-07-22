cmake_minimum_required (VERSION 2.8)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})


set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src) 

set(CubA4ServerSources ${SOURCE_DIR}/main.cpp)

add_executable(CubA4Server ${CubA4ServerSources})

#libs
use_library(CubA4Server ModLoader)
use_library(CubA4Server Network)

#thrid-party include directories
target_include_directories(CubA4Loader PRIVATE ${Boost_INCLUDE_DIRS})

set_target_properties(CubA4Server PROPERTIES FOLDER "Executables")