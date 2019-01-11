cmake_minimum_required (VERSION 3.12)
link_directories(${VULKAN_SDK_LIB} ${SDL_LIBRARY_DIR})

set(RenderVulkanSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(RenderVulkanSourceMathDir ${RenderVulkanSourceDir}/math)
set(RenderVulkanSourceConfigDir ${RenderVulkanSourceDir}/config)
set(RenderVulkanSourceVulkanDir ${RenderVulkanSourceDir}/vulkan)
set(RenderVulkanSourceVulkanUtilDir ${RenderVulkanSourceVulkanDir}/util)
set(RenderVulkanSourceVulkanAddonDir ${RenderVulkanSourceVulkanDir}/addon)
set(RenderVulkanSourceEngineDir ${RenderVulkanSourceDir}/engine)
set(RenderVulkanSourceEngineMemoryDir ${RenderVulkanSourceEngineDir}/memory)
set(RenderVulkanSourceEnginePipelineDir ${RenderVulkanSourceEngineDir}/pipeline)
set(RenderVulkanSourceEngineWorldDir ${RenderVulkanSourceEngineDir}/world)
set(RenderVulkanSourceEngineModelDir ${RenderVulkanSourceEngineDir}/model)
set(RenderVulkanSourceEngineMaterialDir ${RenderVulkanSourceEngineDir}/material)
set(RenderVulkanHeader
	${RenderVulkanSourceDir}/VulkanInfoConst.hpp
)
set(RenderVulkanSourceEngineMemory
	${RenderVulkanSourceEngineMemoryDir}/MemoryHelper.cpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryManager.cpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryAllocator.cpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryBlock.cpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryPart.cpp
)
set(RenderVulkanHeaderEngineMemory
	${RenderVulkanSourceEngineMemoryDir}/MemoryHelper.hpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryManager.hpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryAllocator.hpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryBlock.hpp
	${RenderVulkanSourceEngineMemoryDir}/MemoryPart.hpp
	${RenderVulkanSourceEngineMemoryDir}/IMemoryPart.hpp
	${RenderVulkanSourceEngineMemoryDir}/IMemoryBlock.hpp
)
set(RenderVulkanHeaderMath
	${RenderVulkanSourceMathDir}/Matrix.hpp
	${RenderVulkanSourceMathDir}/Vector.hpp
	${RenderVulkanSourceMathDir}/Math.hpp
)
set(RenderVulkanHeaderEnginePipeline
	${RenderVulkanSourceEnginePipelineDir}/IRenderEnginePipelineSubscriber.hpp
	${RenderVulkanSourceEnginePipelineDir}/RenderChunkCompilerCore.hpp
	${RenderVulkanSourceEnginePipelineDir}/RenderEnginePipeline.hpp
	${RenderVulkanSourceEnginePipelineDir}/RenderChunkCompiler.hpp
	${RenderVulkanSourceEnginePipelineDir}/IRenderEnginePipelineUpdater.hpp
)
set(RenderVulkanSourceEnginePipeline
	${RenderVulkanSourceEnginePipelineDir}/RenderChunkCompilerCore.cpp
	${RenderVulkanSourceEnginePipelineDir}/RenderEnginePipeline.cpp
	${RenderVulkanSourceEnginePipelineDir}/RenderChunkCompiler.cpp
)
set(RenderVulkanSourceEngineWorld
	${RenderVulkanSourceEngineWorldDir}/RenderChunk.cpp
	${RenderVulkanSourceEngineWorldDir}/WorldManager.cpp
)
set(RenderVulkanHeaderEngineWorld
	${RenderVulkanSourceEngineWorldDir}/RenderChunk.hpp
	${RenderVulkanSourceEngineWorldDir}/WorldManager.hpp
)
set(RenderVulkanSourceVulkanUtil
	${RenderVulkanSourceVulkanUtilDir}/ErrorHelper.cpp
)
set(RenderVulkanHeaderVulkanUtil
	${RenderVulkanSourceVulkanUtilDir}/ErrorHelper.hpp
	${RenderVulkanSourceVulkanUtilDir}/VulkanHandlerContainer.hpp
)
set(RenderVulkanSourceEngineModel
	${RenderVulkanSourceEngineModelDir}/ModelManager.cpp
	${RenderVulkanSourceEngineModelDir}/RenderModel.cpp
	${RenderVulkanSourceEngineModelDir}/RenderModel.cpp
)
set(RenderVulkanHeaderEngineModel
	${RenderVulkanSourceEngineModelDir}/ModelManager.hpp
	${RenderVulkanSourceEngineModelDir}/RenderModel.hpp
	${RenderVulkanSourceEngineModelDir}/RenderModel.hpp
)
set(RenderVulkanSourceEngineMaterial
	${RenderVulkanSourceEngineMaterialDir}/Material.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayout.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayoutSetFactory.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayoutBuilder.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialFactory.cpp
	${RenderVulkanSourceEngineMaterialDir}/Shader.cpp
	${RenderVulkanSourceEngineMaterialDir}/VertexShader.cpp
	${RenderVulkanSourceEngineMaterialDir}/FragmentShader.cpp
	${RenderVulkanSourceEngineMaterialDir}/ShaderFactory.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialManager.cpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialBuilder.cpp
)
set(RenderVulkanHeaderEngineMaterial
	${RenderVulkanSourceEngineMaterialDir}/Material.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayout.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayoutSetFactory.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialLayoutBuilder.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialFactory.hpp
	${RenderVulkanSourceEngineMaterialDir}/Shader.hpp
	${RenderVulkanSourceEngineMaterialDir}/VertexShader.hpp
	${RenderVulkanSourceEngineMaterialDir}/FragmentShader.hpp
	${RenderVulkanSourceEngineMaterialDir}/ShaderFactory.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialManager.hpp
	${RenderVulkanSourceEngineMaterialDir}/MaterialBuilder.hpp
)
set(RenderVulkanSourceConfig
	${RenderVulkanSourceConfigDir}/RenderConfig.cpp
)
set(RenderVulkanHeaderConfig
	${RenderVulkanSourceConfigDir}/RenderConfig.hpp
)
set(RenderVulkanHeaderVulkanAddon
	${RenderVulkanSourceVulkanAddonDir}/InstanceAddon.hpp
	${RenderVulkanSourceVulkanAddonDir}/InstanceLayer.hpp
	${RenderVulkanSourceVulkanAddonDir}/InstanceExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/DebugExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/SDLExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/StandardValidationLayer.hpp
	${RenderVulkanSourceVulkanAddonDir}/SwapchainExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/Addon.hpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceAddon.hpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceLayer.hpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceExtension.hpp
)
set(RenderVulkanSourceVulkanAddon
	${RenderVulkanSourceVulkanAddonDir}/InstanceAddon.cpp
	${RenderVulkanSourceVulkanAddonDir}/InstanceLayer.cpp
	${RenderVulkanSourceVulkanAddonDir}/InstanceExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/DebugExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/SDLExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/StandardValidationLayer.cpp
	${RenderVulkanSourceVulkanAddonDir}/SwapchainExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/Addon.cpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceAddon.cpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceLayer.cpp
	${RenderVulkanSourceVulkanAddonDir}/DeviceExtension.cpp
)
set(RenderVulkanSourceVulkan
	${RenderVulkanSourceVulkanDir}/Instance.cpp
	${RenderVulkanSourceVulkanDir}/InstanceBuilder.cpp
	${RenderVulkanSourceVulkanDir}/Surface.cpp
	${RenderVulkanSourceVulkanDir}/Device.cpp
	${RenderVulkanSourceVulkanDir}/DeviceBuilder.cpp
	${RenderVulkanSourceVulkanDir}/PhysicalDevice.cpp
	${RenderVulkanSourceVulkanDir}/Swapchain.cpp
	${RenderVulkanSourceVulkanDir}/SwapchainBuilder.cpp
	${RenderVulkanSourceVulkanDir}/Semaphore.cpp
	${RenderVulkanSourceVulkanDir}/Memory.cpp
	${RenderVulkanSourceVulkanDir}/Pipeline.cpp
	${RenderVulkanSourceVulkanDir}/PipelineBuilder.cpp
	${RenderVulkanSourceVulkanDir}/RenderPassBuilder.cpp
	${RenderVulkanSourceVulkanDir}/RenderPass.cpp
	${RenderVulkanSourceVulkanDir}/DebugMarker.cpp
	${RenderVulkanSourceVulkanDir}/CommandPool.cpp
)
set(RenderVulkanHeaderVulkan
	${RenderVulkanSourceVulkanDir}/Instance.hpp
	${RenderVulkanSourceVulkanDir}/InstanceBuilder.hpp
	${RenderVulkanSourceVulkanDir}/Surface.hpp
	${RenderVulkanSourceVulkanDir}/Device.hpp
	${RenderVulkanSourceVulkanDir}/DeviceBuilder.hpp
	${RenderVulkanSourceVulkanDir}/PhysicalDevice.hpp
	${RenderVulkanSourceVulkanDir}/Swapchain.hpp
	${RenderVulkanSourceVulkanDir}/SwapchainBuilder.hpp
	${RenderVulkanSourceVulkanDir}/Semaphore.hpp
	${RenderVulkanSourceVulkanDir}/Memory.hpp
	${RenderVulkanSourceVulkanDir}/Pipeline.hpp
	${RenderVulkanSourceVulkanDir}/PipelineBuilder.hpp
	${RenderVulkanSourceVulkanDir}/RenderPassBuilder.hpp
	${RenderVulkanSourceVulkanDir}/RenderPass.hpp
	${RenderVulkanSourceVulkanDir}/DebugMarker.hpp
	${RenderVulkanSourceVulkanDir}/CommandPool.hpp
)
set(RenderVulkanSourceEngine
	${RenderVulkanSourceEngineDir}/RenderEngine.cpp
	${RenderVulkanSourceEngineDir}/Presentaion.cpp
	${RenderVulkanSourceEngineDir}/Render.cpp
	${RenderVulkanSourceEngineDir}/RenderManager.cpp
	${RenderVulkanSourceEngineDir}/ResourceManager.cpp
	${RenderVulkanSourceEngineDir}/RenderGameHandler.cpp
	${RenderVulkanSourceEngineDir}/RenderEngineCore.cpp
)
set(RenderVulkanHeaderEngine
	${RenderVulkanSourceEngineDir}/RenderEngine.hpp
	${RenderVulkanSourceEngineDir}/Presentaion.hpp
	${RenderVulkanSourceEngineDir}/Render.hpp
	${RenderVulkanSourceEngineDir}/RenderManager.hpp
	${RenderVulkanSourceEngineDir}/ResourceManager.hpp
	${RenderVulkanSourceEngineDir}/RenderGameHandler.hpp
	${RenderVulkanSourceEngineDir}/RenderEngineCore.hpp
)

set(RenderVulkanHeaders
	${RenderVulkanSourceDir}/VulkanInfo.hpp
	${RenderVulkanHeaderEngine}
	${RenderVulkanHeaderVulkan}
	${RenderVulkanHeaderVulkanAddon}
	${RenderVulkanHeaderConfig}
	${RenderVulkanHeaderEngineMaterial}
	${RenderVulkanHeaderEngineModel}
	${RenderVulkanHeaderVulkanUtil}
	${RenderVulkanHeaderEngineWorld}
	${RenderVulkanHeaderEnginePipeline}
	${RenderVulkanHeaderMath}
	${RenderVulkanHeaderEngineMemory}
	${RenderVulkanHeader}
)
set(RenderVulkanSources
	${RenderVulkanSourceDir}/VulkanInfo.cpp
	${RenderVulkanSourceDir}/Loader.cpp
	${RenderVulkanSourceEngine}
	${RenderVulkanSourceVulkan}
	${RenderVulkanSourceVulkanAddon}
	${RenderVulkanSourceConfig}
	${RenderVulkanSourceEngineMaterial}
	${RenderVulkanSourceEngineModel}
	${RenderVulkanSourceVulkanUtil}
	${RenderVulkanSourceEngineWorld}
	${RenderVulkanSourceEnginePipeline}
	${RenderVulkanSourceEngineMemory}
)

source_group("${SOURCE_GROUP_HEADER_START}engine" FILES ${RenderVulkanHeaderEngine})
source_group("${SOURCE_GROUP_SOURCE_START}engine" FILES ${RenderVulkanSourceEngine})
source_group("${SOURCE_GROUP_HEADER_START}vulkan" FILES ${RenderVulkanHeaderVulkan})
source_group("${SOURCE_GROUP_SOURCE_START}vulkan" FILES ${RenderVulkanSourceVulkan})
source_group("${SOURCE_GROUP_HEADER_START}vulkan${SOURCE_GROUP_SEP}addon" FILES ${RenderVulkanHeaderVulkanAddon})
source_group("${SOURCE_GROUP_SOURCE_START}vulkan${SOURCE_GROUP_SEP}addon" FILES ${RenderVulkanSourceVulkanAddon})
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${RenderVulkanHeaderConfig})
source_group("${SOURCE_GROUP_SOURCE_START}config" FILES ${RenderVulkanSourceConfig})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}material" FILES ${RenderVulkanHeaderEngineMaterial})
source_group("${SOURCE_GROUP_SOURCE_START}engine${SOURCE_GROUP_SEP}material" FILES ${RenderVulkanSourceEngineMaterial})
source_group("${SOURCE_GROUP_SOURCE_START}engine${SOURCE_GROUP_SEP}model" FILES ${RenderVulkanSourceEngineModel})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}model" FILES ${RenderVulkanHeaderEngineModel})
source_group("${SOURCE_GROUP_HEADER_START}vulkan${SOURCE_GROUP_SEP}util" FILES ${RenderVulkanHeaderVulkanUtil})
source_group("${SOURCE_GROUP_SOURCE_START}vulkan${SOURCE_GROUP_SEP}util" FILES ${RenderVulkanSourceVulkanUtil})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}world" FILES ${RenderVulkanHeaderEngineWorld})
source_group("${SOURCE_GROUP_SOURCE_START}engine${SOURCE_GROUP_SEP}world" FILES ${RenderVulkanSourceEngineWorld})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}pipeline" FILES ${RenderVulkanHeaderEnginePipeline})
source_group("${SOURCE_GROUP_SOURCE_START}engine${SOURCE_GROUP_SEP}pipeline" FILES ${RenderVulkanSourceEnginePipeline})

add_irs(${CMAKE_CURRENT_LIST_DIR} irs_resources)
source_group("resources" FILES ${irs_resources})
source_group("${SOURCE_GROUP_HEADER_START}math" FILES ${RenderVulkanHeaderMath})
source_group("${SOURCE_GROUP_HEADER_START}engine${SOURCE_GROUP_SEP}memory" FILES ${RenderVulkanHeaderEngineMemory})
source_group("${SOURCE_GROUP_SOURCE_START}engine${SOURCE_GROUP_SEP}memory" FILES ${RenderVulkanSourceEngineMemory})

add_library(RenderVulkan SHARED ${RenderVulkanHeaders} ${RenderVulkanSources} ${irs_resources})

#third-party library

find_library(vulkan-1 PATHS ${VULKAN_SDK_LIB} NO_DEFAULT_PATH)
find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)

target_include_directories(RenderVulkan PRIVATE ${VULKAN_SDK_INCLUDE})
target_include_directories(RenderVulkan PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(RenderVulkan PRIVATE ${VULKAN_LIBRARY_NAME} SDL2 SDL2main)

target_include_directories(RenderVulkan PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(RenderVulkan PRIVATE Boost::filesystem)

use_base_library(RenderVulkan CoreBase)
use_base_library(RenderVulkan ModBase)
use_base_library(RenderVulkan RenderBase)

#set output directory
set_target_properties( RenderVulkan
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
	LIBRARY_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(RenderVulkan PROPERTIES FOLDER "Render")