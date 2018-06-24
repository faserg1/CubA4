cmake_minimum_required (VERSION 2.8)

set(RenderBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(RenderBaseIncludeConfigDir ${RenderBaseIncludeDir}/config)
set(RenderBaseIncludeWindowDir ${RenderBaseIncludeDir}/window)
set(RenderBaseIncludeEngineDir ${RenderBaseIncludeDir}/engine)
set(RenderBaseHeaderConfig
	${RenderBaseIncludeConfigDir}/IRenderConfig.hpp
)
set(RenderBaseHeaderWindow
	${RenderBaseIncludeWindowDir}/IWindow.hpp
)
set(RenderBaseHeaderEngine
	${RenderBaseIncludeEngineDir}/IRenderEngine.hpp
	${RenderBaseIncludeEngineDir}/IMaterialLayout.hpp
	${RenderBaseIncludeEngineDir}/IMaterial.hpp
	${RenderBaseIncludeEngineDir}/IMaterialFactory.hpp
	${RenderBaseIncludeEngineDir}/IMaterialLayoutSetFactory.hpp
	${RenderBaseIncludeEngineDir}/IMaterialLayoutBuilder.hpp
)

set(RenderBaseHeaders 
	${RenderBaseIncludeDir}/RenderExportHelper.hpp
	${RenderBaseIncludeDir}/IRenderInfo.hpp
	${RenderBaseHeaderEngine}
	${RenderBaseHeaderWindow}
	${RenderBaseHeaderConfig}
	)
source_group("${SOURCE_GROUP_HEADER_START}engine" FILES ${RenderBaseHeaderEngine})
source_group("${SOURCE_GROUP_HEADER_START}window" FILES ${RenderBaseHeaderWindow})
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${RenderBaseHeaderConfig})

add_library(RenderBase INTERFACE)
target_include_directories(RenderBase INTERFACE include)

#Visibility for IDE
add_custom_target(RenderBaseProject SOURCES ${RenderBaseHeaders})

set_target_properties(RenderBaseProject PROPERTIES FOLDER "API")