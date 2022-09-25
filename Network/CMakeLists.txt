cmake_minimum_required (VERSION 3.12)

set(NetworkIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(NetworkSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE NetworkSources
    "${NetworkIncludeDir}/**/*.hpp"
    "${NetworkIncludeDir}/*.hpp"
    "${NetworkSourceDir}/**/*.hpp"
    "${NetworkSourceDir}/**/*.cpp"
    "${NetworkSourceDir}/*.hpp"
    "${NetworkSourceDir}/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${NetworkSources})


#library
add_library(Network SHARED ${NetworkSources})

use_base_library(Network CoreBase)

#self include directories
target_include_directories(Network PUBLIC ${NetworkIncludeDir})

#set defines for library export
target_compile_definitions(Network PRIVATE NETWORK_LIBRARY)

#thridparty link libraries
target_link_libraries(Network PRIVATE Boost::boost)

#system libraries
use_thread_library(Network)

set_target_properties(Network PROPERTIES FOLDER "Libs")