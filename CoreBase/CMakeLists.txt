cmake_minimum_required (VERSION 3.12)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE CoreBaseHeaders
    "${CoreBaseIncludeDir}/**/*.hpp"
    "${CoreBaseIncludeDir}/*.hpp"
)

source_group(TREE ${CoreBaseIncludeDir} FILES ${CoreBaseHeaders})

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")