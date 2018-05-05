cmake_minimum_required (VERSION 2.8)

link_directories(
#third party
	${Boost_LIBRARY_DIRS})

#paths, headers, sources
set (ModLoaderHeadersPath ${CMAKE_CURRENT_LIST_DIR}/include)
set (ModLoaderSourcesPath ${CMAKE_CURRENT_LIST_DIR}/src)

set(ModLoaderHeadersLoader
	include/loader/ModLoader.hpp
	src/loader/ModLibrary.hpp
)

set(ModLoaderSourcesLoader 
	src/loader/ModLibrary.cpp
	src/loader/ModLoader.cpp
)

source_group("Header Files\\loader" FILES ${ModLoaderHeadersLoader})
source_group("Source Files\\loader" FILES ${ModLoaderSourcesLoader})

set (ModLoaderHeaders
	${ModLoaderHeadersLoader}
	include/ModLoaderLibrary.hpp				
)
set (ModLoaderSources
	${ModLoaderSourcesLoader}
	src/common.cpp
)

set(MoadLoaderTotal
	${ModLoaderHeaders}
	${ModLoaderSources}
)

#library
add_library(ModLoader SHARED ${ModLoaderHeaders} ${ModLoaderSources})

#link
#target_link_libraries (ModLoader LINK_INTERFACE_LIBRARIES ModBase)
#target_link_libraries (ModLoader LINK_INTERFACE_LIBRARIES RenderBase)

#self include directories
target_include_directories(ModLoader PUBLIC ${ModLoaderHeadersPath})

#thrid-party
target_include_directories(ModLoader PRIVATE ${Boost_INCLUDE_DIRS})

#libs
get_target_property(MOD_BASE_INCLUDE_DIRECTORIES ModBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ModLoader PUBLIC ${MOD_BASE_INCLUDE_DIRECTORIES})

#set defines for library export
target_compile_definitions(ModLoader PRIVATE MOD_LOADER_LIBRARY)

#thridparty link libraries
target_link_libraries(ModLoader PRIVATE Boost::filesystem)

set_target_properties(ModLoader PROPERTIES FOLDER "Libs")