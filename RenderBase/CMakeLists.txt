cmake_minimum_required (VERSION 3.12)

set(RenderBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(RenderBaseIncludeConfigDir ${RenderBaseIncludeDir}/config)
set(RenderBaseIncludeWindowDir ${RenderBaseIncludeDir}/window)
set(RenderBaseIncludeEngineDir ${RenderBaseIncludeDir}/engine)
set(RenderBaseIncludeEngineWorldDir ${RenderBaseIncludeEngineDir}/world)
set(RenderBaseIncludeEngineModelDir ${RenderBaseIncludeEngineDir}/model)
set(RenderBaseIncludeEngineMaterialDir ${RenderBaseIncludeEngineDir}/material)
set(RenderBaseHeaderEngineWorld
	${RenderBaseIncludeEngineWorldDir}/IWorldManager.hpp
)
set(RenderBaseHeaderEngineModel
	${RenderBaseIncludeEngineModelDir}/IModelManager.hpp
	${RenderBaseIncludeEngineModelDir}/IRenderModel.hpp
)
set(RenderBaseHeaderConfig
	${RenderBaseIncludeConfigDir}/IRenderConfig.hpp
)
set(RenderBaseHeaderWindow
	${RenderBaseIncludeWindowDir}/IWindow.hpp
)
set(RenderBaseHeaderEngine
	${RenderBaseIncludeEngineDir}/IRenderEngine.hpp
	${RenderBaseIncludeEngineDir}/IRenderManager.hpp
)
set(RenderBaseHeaderEngineMaterial
	${RenderBaseIncludeEngineMaterialDir}/IMaterialLayout.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterial.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterialFactory.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterialLayoutSetFactory.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterialLayoutBuilder.hpp
	${RenderBaseIncludeEngineMaterialDir}/IShader.hpp
	${RenderBaseIncludeEngineMaterialDir}/IVertexShader.hpp
	${RenderBaseIncludeEngineMaterialDir}/IFragmentShader.hpp
	${RenderBaseIncludeEngineMaterialDir}/IShaderFactory.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterialManager.hpp
	${RenderBaseIncludeEngineMaterialDir}/IMaterialBuilder.hpp
	${RenderBaseIncludeEngineMaterialDir}/ITexture.hpp
	${RenderBaseIncludeEngineMaterialDir}/ITextureImporter.hpp
)

set(RenderBaseHeaders 
	${RenderBaseIncludeDir}/RenderExportHelper.hpp
	${RenderBaseIncludeDir}/IRenderInfo.hpp
	${RenderBaseHeaderEngine}
	${RenderBaseHeaderEngineMaterial}
	${RenderBaseHeaderWindow}
	${RenderBaseHeaderConfig}
	${RenderBaseHeaderEngineModel}
	${RenderBaseHeaderEngineWorld}
	)
source_group("${SOURCE_GROUP_HEADER_START}engine" FILES ${RenderBaseHeaderEngine})
source_group("${SOURCE_GROUP_HEADER_START}window" FILES ${RenderBaseHeaderWindow})
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${RenderBaseHeaderConfig})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}material" FILES ${RenderBaseHeaderEngineMaterial})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}model" FILES ${RenderBaseHeaderEngineModel})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}world" FILES ${RenderBaseHeaderEngineWorld})

add_library(RenderBase INTERFACE)
target_include_directories(RenderBase INTERFACE include)

#Visibility for IDE
add_custom_target(RenderBaseProject SOURCES ${RenderBaseHeaders})

set_target_properties(RenderBaseProject PROPERTIES FOLDER "API")