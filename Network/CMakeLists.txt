cmake_minimum_required (VERSION 2.8)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})
	
set (NetworkHeadersPath ${CMAKE_CURRENT_LIST_DIR}/include)
set (NetworkSourcesPath ${CMAKE_CURRENT_LIST_DIR}/src)

set(NetworkHeaders
	${NetworkHeadersPath}/NetworkLibrary.hpp
)

set(NetworkSources
	${NetworkSourcesPath}/common.cpp
)

#library
add_library(Network SHARED ${NetworkHeaders} ${NetworkSources})

#thrid-party
target_include_directories(Network PRIVATE ${Boost_INCLUDE_DIRS})

#set defines for library export
target_compile_definitions(Network PRIVATE NETWORK_LIBRARY)

#thridparty link libraries
target_link_libraries(Network PRIVATE Boost::system)

set_target_properties(Network PROPERTIES FOLDER "Libs")