cmake_minimum_required (VERSION 3.12)

#paths, headers, sources
set (ModLoaderHeadersPath ${CMAKE_CURRENT_LIST_DIR}/include)
set (ModLoaderSourcesPath ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE ModLoaderSources
    "${ModLoaderHeadersPath}/**/*.hpp"
    "${ModLoaderSourcesPath}/**/*.hpp"
    "${ModLoaderSourcesPath}/**/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ModLoaderSources})

#library
add_library(ModLoader SHARED ${ModLoaderSources})

#self include directories
target_include_directories(ModLoader PUBLIC ${ModLoaderHeadersPath})

#libs
use_base_library(ModLoader CoreBase)
use_base_library(ModLoader ModBase)

#set defines for library export
target_compile_definitions(ModLoader PRIVATE MOD_LOADER_LIBRARY)

#thridparty link libraries
target_link_libraries(ModLoader PRIVATE Boost::boost Boost::filesystem fmt::fmt)

#system libraries
use_system_loader_library(ModLoader)

set_target_properties(ModLoader PROPERTIES FOLDER "Libs")