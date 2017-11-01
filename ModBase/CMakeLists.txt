cmake_minimum_required (VERSION 2.8)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)

set(ModBaseHeaders 
	${ModBaseIncludeDir}/ExportHelper.hpp
	${ModBaseIncludeDir}/ModInfo.hpp
)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})