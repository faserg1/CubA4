cmake_minimum_required (VERSION 2.8)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src) 

set(CubA4ServerSources ${SOURCE_DIR}/main.cpp)

add_executable(CubA4Server ${CubA4ServerSources})

#libs
get_target_property(MOD_LOADER_INCLUDE_DIRECTORIES ModLoader INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CubA4Server INTERFACE ${MOD_LOADER_INCLUDE_DIRECTORIES})

target_link_libraries(CubA4Server PRIVATE ModLoader)