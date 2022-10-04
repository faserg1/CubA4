cmake_minimum_required (VERSION 3.12)

set(ModVanillaResourcesDir ${CMAKE_CURRENT_LIST_DIR}/data)
set(ModVanillaIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE ModVanillaSources
    "${ModVanillaIncludeDir}/**/*.hpp"
    "${ModVanillaIncludeDir}/*.hpp"
    "${ModVanillaSourceDir}/**/*.hpp"
    "${ModVanillaSourceDir}/**/*.cpp"
    "${ModVanillaSourceDir}/*.hpp"
    "${ModVanillaSourceDir}/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ModVanillaSources})

add_irs(${CMAKE_CURRENT_LIST_DIR} irs_resources)
source_group("resources" FILES ${irs_resources})

add_library(ModVanilla SHARED ${ModVanillaSources} ${irs_resources})

use_base_library(ModVanilla ModBase)
use_base_library(ModVanilla CoreBase)
use_base_library(ModVanilla RenderBase)

add_custom_command(TARGET ModVanilla PRE_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E remove_directory ${RESOURCES_OUTPUT_DIRECTORY}/mod/vanilla
	)

add_custom_command(TARGET ModVanilla POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_directory ${ModVanillaResourcesDir} ${RESOURCES_OUTPUT_DIRECTORY}
	)

#set output directory
set_target_properties( ModVanilla
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(ModVanilla PROPERTIES FOLDER "Mods")