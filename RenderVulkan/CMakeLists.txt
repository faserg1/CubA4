cmake_minimum_required (VERSION 2.8)

link_directories(${VULKAN_SDK_LIB} ${SDL_LIBRARY_DIR})

set(RenderVulkanSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(RenderVulkanSourceVulkanDir ${RenderVulkanSourceDir}/vulkan)
set(RenderVulkanSourceVulkanAddonDir ${RenderVulkanSourceVulkanDir}/addon)
set(RenderVulkanSourceEngineDir ${RenderVulkanSourceDir}/engine)
set(RenderVulkanHeaderVulkanAddon
	${RenderVulkanSourceVulkanAddonDir}/VulkanInstanceAddon.hpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanLayer.hpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanDebugExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanSDLExtension.hpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanStandardValidationLayer.hpp
)
set(RenderVulkanSourceVulkanAddon
	${RenderVulkanSourceVulkanAddonDir}/VulkanInstanceAddon.cpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanLayer.cpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanDebugExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanSDLExtension.cpp
	${RenderVulkanSourceVulkanAddonDir}/VulkanStandardValidationLayer.cpp
)
set(RenderVulkanSourceVulkan
	${RenderVulkanSourceVulkanDir}/VulkanInstance.cpp
	${RenderVulkanSourceVulkanDir}/VulkanInstanceBuilder.cpp
)
set(RenderVulkanHeaderVulkan
	${RenderVulkanSourceVulkanDir}/VulkanInstance.hpp
	${RenderVulkanSourceVulkanDir}/VulkanInstanceBuilder.hpp
)
set(RenderVulkanSourceEngine
	${RenderVulkanSourceEngineDir}/VulkanRenderEngine.cpp
)
set(RenderVulkanHeaderEngine
	${RenderVulkanSourceEngineDir}/VulkanRenderEngine.hpp
)

set(RenderVulkanHeaders
	${RenderVulkanSourceDir}/VulkanInfo.hpp
	${RenderVulkanHeaderEngine}
	${RenderVulkanHeaderVulkan}
	${RenderVulkanHeaderVulkanAddon}
)
source_group("${SOURCE_GROUP_HEADER_START}engine" FILES ${RenderVulkanHeaderEngine})

set(RenderVulkanSources
	${RenderVulkanSourceDir}/VulkanInfo.cpp
	${RenderVulkanSourceDir}/Loader.cpp
	${RenderVulkanSourceEngine}
	${RenderVulkanSourceVulkan}
	${RenderVulkanSourceVulkanAddon}
)
source_group("${SOURCE_GROUP_SOURCE_START}engine" FILES ${RenderVulkanSourceEngine})
source_group("${SOURCE_GROUP_HEADER_START}vulkan" FILES ${RenderVulkanHeaderVulkan})
source_group("${SOURCE_GROUP_SOURCE_START}vulkan" FILES ${RenderVulkanSourceVulkan})
source_group("${SOURCE_GROUP_HEADER_START}vulkan${SOURCE_GROUP_SEP}addon" FILES ${RenderVulkanHeaderVulkanAddon})
source_group("${SOURCE_GROUP_SOURCE_START}vulkan${SOURCE_GROUP_SEP}addon" FILES ${RenderVulkanSourceVulkanAddon})

add_library(RenderVulkan SHARED ${RenderVulkanHeaders} ${RenderVulkanSources})

find_library(vulkan-1 PATHS ${VULKAN_SDK_LIB} NO_DEFAULT_PATH)
find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)

target_include_directories(RenderVulkan PRIVATE ${VULKAN_SDK_INCLUDE})
target_include_directories(RenderVulkan PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(RenderVulkan PRIVATE vulkan-1 SDL2 SDL2main)

get_target_property(RENDER_BASE_INCLUDE_DIRECTORIES RenderBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(RenderVulkan PUBLIC ${RENDER_BASE_INCLUDE_DIRECTORIES})

get_target_property(CORE_BASE_INCLUDE_DIRECTORIES CoreBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(RenderVulkan PUBLIC ${CORE_BASE_INCLUDE_DIRECTORIES})

#set output directory
set_target_properties( RenderVulkan
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(RenderVulkan PROPERTIES FOLDER "Render")