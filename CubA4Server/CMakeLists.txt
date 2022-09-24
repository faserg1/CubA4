cmake_minimum_required (VERSION 3.12)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})


set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src) 

set(CubA4ServerSources ${SOURCE_DIR}/main.cpp)

add_executable(CubA4Server ${CubA4ServerSources})

#libs
use_library(CubA4Server ModLoader)
use_library(CubA4Server Network)

#thridparty link libraries
target_link_libraries(CubA4Server PRIVATE Boost::boost)

#system libraries
use_thread_library(CubA4Server)
use_system_loader_library(CubA4Server)

set_target_properties(CubA4Server PROPERTIES FOLDER "Executables")