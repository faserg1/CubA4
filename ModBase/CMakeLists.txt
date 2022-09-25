cmake_minimum_required (VERSION 3.12)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
file(GLOB_RECURSE ModBaseHeaders
    "${ModBaseIncludeDir}/**/*.hpp"
    "${ModBaseIncludeDir}/**/*.cpp"
    "${ModBaseIncludeDir}/*.hpp"
    "${ModBaseIncludeDir}/*.cpp"
)
source_group(TREE ${ModBaseIncludeDir} FILES ${ModBaseHeaders})

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")