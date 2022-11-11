cmake_minimum_required (VERSION 3.12)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})


set(CubA4ServerSourceDir ${CMAKE_CURRENT_LIST_DIR}/src) 

file(GLOB_RECURSE CubA4ServerSources
    "${CubA4ServerSourceDir}/**/*.hpp"
    "${CubA4ServerSourceDir}/**/*.cpp"
    "${CubA4ServerSourceDir}/*.hpp"
    "${CubA4ServerSourceDir}/*.cpp"
)

source_group(TREE ${CubA4ServerSourceDir} FILES ${CubA4ServerSources})

add_executable(CubA4Server ${CubA4ServerSources})
target_compile_features(CubA4Server PRIVATE ${TARGET_CXX_STD})

#libs
use_library(CubA4Server ModLoader)
use_library(CubA4Server Network)

#thridparty link libraries
target_link_libraries(CubA4Server PRIVATE Boost::boost)

#system libraries
use_thread_library(CubA4Server)
use_system_loader_library(CubA4Server)

set_target_properties(CubA4Server PROPERTIES FOLDER "Executables")

set_target_properties( CubA4Server
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
	RUNTIME_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
)