cmake_minimum_required (VERSION 3.12)

set(RenderVulkanSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE RenderVulkanSources
    "${RenderVulkanSourceDir}/**/*.hpp"
    "${RenderVulkanSourceDir}/**/*.cpp"
    "${RenderVulkanSourceDir}/*.hpp"
    "${RenderVulkanSourceDir}/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${RenderVulkanSources})

link_directories(${VULKAN_SDK_LIB})

add_irs(${CMAKE_CURRENT_LIST_DIR} irs_resources)
source_group("resources" FILES ${irs_resources})

set(ASSETS_SRC_FOLDER ${CMAKE_CURRENT_LIST_DIR}/assets-src)
set(SHADERS_IN_FOLDER ${ASSETS_SRC_FOLDER}/shaders)
set(SHADERS_OUT_FOLDER ${CMAKE_CURRENT_LIST_DIR}/irs/shaders)


add_library(RenderVulkan SHARED ${RenderVulkanSources} ${irs_resources})
target_compile_features(RenderVulkan PRIVATE ${TARGET_CXX_STD})
target_include_directories(RenderVulkan PRIVATE src)

#third-party library


target_include_directories(RenderVulkan PRIVATE ${VULKAN_SDK_INCLUDE})
target_link_libraries(RenderVulkan PRIVATE
    ${VULKAN_LIBRARY_NAME}
    range-v3 range-v3-meta range-v3::meta range-v3-concepts
    nlohmann_json nlohmann_json::nlohmann_json SDL2::SDL2 SDL2::SDL2main glm::glm png)

#use_library(RenderVulkan zlib)
#use_library(RenderVulkan pnglib)

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

include(${CMAKE_CURRENT_LIST_DIR}/shaders.cmake)
add_dependencies(RenderVulkan IRS_GENERATION)