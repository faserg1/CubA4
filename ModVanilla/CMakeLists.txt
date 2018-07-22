cmake_minimum_required (VERSION 2.8)

set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(ModVanillaHeaders 
	${ModVanillaSourceDir}/ModVanillaInfo.hpp)

set(ModVanillaSources 
	${ModVanillaSourceDir}/ModVanillaInfo.cpp
	${ModVanillaSourceDir}/ExportMod.cpp
	)
	
add_library(ModVanilla SHARED ${ModVanillaHeaders} ${ModVanillaSources})

use_base_library(ModVanilla ModBase)
use_base_library(ModVanilla CoreBase)
use_base_library(ModVanilla RenderBase)

#set output directory
set_target_properties( ModVanilla
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(ModVanilla PROPERTIES FOLDER "Mods")