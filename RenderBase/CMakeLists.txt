cmake_minimum_required (VERSION 2.8)

set(RenderBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(RenderBaseIncludeEngineDir ${RenderBaseIncludeDir}/engine)
set(RenderBaseHeaderEngine
	${RenderBaseIncludeEngineDir}/IRenderEngine.hpp
)

set(RenderBaseHeaders 
	${RenderBaseIncludeDir}/RenderExportHelper.hpp
	${RenderBaseIncludeDir}/IRenderInfo.hpp
	${RenderBaseHeaderEngine}
	)
source_group("${SOURCE_GROUP_HEADER_START}engine" FILES ${RenderBaseHeaderEngine})

add_library(RenderBase INTERFACE)
target_include_directories(RenderBase INTERFACE include)

#Visibility for IDE
add_custom_target(RenderBaseProject SOURCES ${RenderBaseHeaders})

set_target_properties(RenderBaseProject PROPERTIES FOLDER "API")