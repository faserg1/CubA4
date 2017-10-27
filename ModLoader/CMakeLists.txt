cmake_minimum_required (VERSION 2.8)

set (ModLoaderHeadersPath ${CMAKE_CURRENT_LIST_DIR}/include)

set (ModLoaderHeaders include/ModLoaderLibrary.hpp)
set (ModLoaderSources src/common.cpp)

add_library(ModLoader SHARED ${ModLoaderHeaders} ${ModLoaderSources})

target_include_directories(ModLoader PRIVATE ${BOOST_INCLUDE_DIR})
target_include_directories(ModLoader PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(ModLoader PRIVATE MOD_LOADER_LIBRARY)