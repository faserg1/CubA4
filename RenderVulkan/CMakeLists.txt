cmake_minimum_required (VERSION 2.8)

link_directories(${VULKAN_SDK_LIB})

set(RenderVulkanSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(RenderVulkanSources
	${RenderVulkanSourceDir}/VulkanInfo.hpp
	${RenderVulkanSourceDir}/VulkanInfo.cpp
	${RenderVulkanSourceDir}/Loader.cpp
	)

add_library(RenderVulkan SHARED ${RenderVulkanSources})

find_library(vulkan-1 PATHS ${VULKAN_SDK_LIB} NO_DEFAULT_PATH)

target_include_directories(RenderVulkan PRIVATE ${VULKAN_SDK_INCLUDE})

target_link_libraries(RenderVulkan PRIVATE vulkan-1)

get_target_property(RENDER_BASE_INCLUDE_DIRECTORIES RenderBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(RenderVulkan PUBLIC ${RENDER_BASE_INCLUDE_DIRECTORIES})

#set output directory
set_target_properties( RenderVulkan
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${RENDER_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(RenderVulkan PROPERTIES FOLDER "Render")