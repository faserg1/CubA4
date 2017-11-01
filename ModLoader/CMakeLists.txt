cmake_minimum_required (VERSION 2.8)

#paths, headers, sources
set (ModLoaderHeadersPath ${CMAKE_CURRENT_LIST_DIR}/include)

set (ModLoaderHeaders
					include/ModLoaderLibrary.hpp
					include/loader/ModLoader.hpp)
set (ModLoaderSources
					src/loader/ModLoader.cpp
					src/common.cpp)

#library
add_library(ModLoader SHARED ${ModLoaderHeaders} ${ModLoaderSources})

#link
#target_link_libraries (ModLoader LINK_INTERFACE_LIBRARIES ModBase)
#target_link_libraries (ModLoader LINK_INTERFACE_LIBRARIES RenderBase)

#self include directories
target_include_directories(ModLoader PUBLIC ${ModLoaderHeadersPath})

#thrid-party
target_include_directories(ModLoader PRIVATE ${BOOST_INCLUDE_DIR})

#libs
get_target_property(MOD_BASE_INCLUDE_DIRECTORIES ModBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ModLoader PUBLIC ${MOD_BASE_INCLUDE_DIRECTORIES})

#set defines for library export
target_compile_definitions(ModLoader PRIVATE MOD_LOADER_LIBRARY)