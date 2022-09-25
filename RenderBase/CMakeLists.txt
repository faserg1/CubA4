cmake_minimum_required (VERSION 3.12)

set(RenderBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE RenderBaseHeaders
    "${RenderBaseIncludeDir}/**/*.hpp"
    "${RenderBaseIncludeDir}/*.hpp"
)

source_group(TREE ${RenderBaseIncludeDir} FILES ${RenderBaseHeaders})

add_library(RenderBase INTERFACE)
target_include_directories(RenderBase INTERFACE include)

#Visibility for IDE
add_custom_target(RenderBaseProject SOURCES ${RenderBaseHeaders})

set_target_properties(RenderBaseProject PROPERTIES FOLDER "API")