cmake_minimum_required (VERSION 2.8)

set(RenderBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)

set(RenderBaseHeaders 
	${RenderBaseIncludeDir}/ExportHelper.hpp
	${RenderBaseIncludeDir}/RenderInfo.hpp
	${RenderBaseIncludeDir}/RenderEngine.hpp
	)

add_library(RenderBase INTERFACE)
target_include_directories(RenderBase INTERFACE include)

#Visibility for IDE
add_custom_target(RenderBaseProject SOURCES ${RenderBaseHeaders})