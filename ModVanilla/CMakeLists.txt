cmake_minimum_required (VERSION 3.12)

set(ModVanillaResourcesDir ${CMAKE_CURRENT_LIST_DIR}/resources)

set(ModVanillaIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModVanillaIncludeBlockDir ${ModVanillaIncludeDir}/block)

set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(ModVanillaSourceWorldDir ${ModVanillaSourceDir}/world)
set(ModVanillaSourceManagerDir ${ModVanillaSourceDir}/manager)
set(ModVanillaSourceBlockDir ${ModVanillaSourceDir}/block)
set(ModVanillaSourceRenderDir ${ModVanillaSourceDir}/render)
set(ModVanillaSourceStartupDir ${ModVanillaSourceDir}/startup)
set(ModVanillaSourceCoreDir ${ModVanillaSourceDir}/core)
set(ModVanillaSourceCoreInfoDir ${ModVanillaSourceCoreDir}/info)
set(ModVanillaSourceWorld
	${ModVanillaSourceWorldDir}/TestWorldGenerator.cpp
	${ModVanillaSourceWorldDir}/TestWorld.cpp
)
set(ModVanillaHeaderWorld
	${ModVanillaSourceWorldDir}/TestWorldGenerator.hpp
	${ModVanillaSourceWorldDir}/TestWorld.hpp
)
set(ModVanillaSourceManager
	${ModVanillaSourceManagerDir}/ModManager.cpp
	${ModVanillaSourceManagerDir}/ModRenderManager.cpp
	${ModVanillaSourceManagerDir}/ModBlockManager.cpp
	${ModVanillaSourceManagerDir}/ModItemManager.cpp
)
set(ModVanillaHeaderManager
	${ModVanillaSourceManagerDir}/ModManager.hpp
	${ModVanillaSourceManagerDir}/ModRenderManager.hpp
	${ModVanillaSourceManagerDir}/ModBlockManager.hpp
	${ModVanillaSourceManagerDir}/ModItemManager.hpp
)
set(ModVanillaSourceBlock
	${ModVanillaSourceBlockDir}/TestBlock.cpp
)
set(ModVanillaHeaderBlock
	${ModVanillaIncludeBlockDir}/TestBlock.hpp
)
set(ModVanillaSourceRender
	${ModVanillaSourceRenderDir}/BlockModel.cpp
)
set(ModVanillaHeaderRender
	${ModVanillaSourceRenderDir}/BlockModel.hpp
)
set(ModVanillaSourceStartup
	${ModVanillaSourceStartupDir}/RenderStartup.cpp
	${ModVanillaSourceStartupDir}/WorldSetup.cpp
)
set(ModVanillaHeaderStartup
	${ModVanillaSourceStartupDir}/RenderStartup.hpp
	${ModVanillaSourceStartupDir}/WorldSetup.hpp
)
set(ModVanillaSource
	${ModVanillaSourceDir}/ModVanilla.cpp
)
set(ModVanillaHeader
	${ModVanillaSourceDir}/ModVanilla.hpp
	${ModVanillaIncludeDir}/IModVanilla.hpp
)
set(ModVanillaSourceCoreInfo
	${ModVanillaSourceCoreInfoDir}/Version.cpp
	${ModVanillaSourceCoreInfoDir}/VersionDependency.cpp
)
set(ModVanillaHeaderCoreInfo
	${ModVanillaSourceCoreInfoDir}/Version.hpp
	${ModVanillaSourceCoreInfoDir}/VersionDependency.hpp
)

set(ModVanillaHeaders 
	${ModVanillaSourceDir}/ModVanillaInfo.hpp
	${ModVanillaHeaderCoreInfo}
	${ModVanillaHeader}
	${ModVanillaHeaderStartup}
	${ModVanillaHeaderRender}
	${ModVanillaHeaderBlock}
	${ModVanillaHeaderManager}
	${ModVanillaHeaderWorld})
source_group("${SOURCE_GROUP_HEADER_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaHeaderCoreInfo})

set(ModVanillaSources
	${ModVanillaSourceDir}/ModVanillaInfo.cpp
	${ModVanillaSourceDir}/ExportMod.cpp
	${ModVanillaSourceCoreInfo}
	${ModVanillaSource}
	${ModVanillaSourceStartup}
	${ModVanillaSourceRender}
	${ModVanillaSourceBlock}
	${ModVanillaSourceManager}
	${ModVanillaSourceWorld}
	)
source_group("${SOURCE_GROUP_SOURCE_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaSourceCoreInfo})
source_group("${SOURCE_GROUP_HEADER_START}startup" FILES ${ModVanillaHeaderStartup})
source_group("${SOURCE_GROUP_SOURCE_START}startup" FILES ${ModVanillaSourceStartup})

add_irs(${CMAKE_CURRENT_LIST_DIR} irs_resources)
source_group("resources" FILES ${irs_resources})
source_group("${SOURCE_GROUP_HEADER_START}render" FILES ${ModVanillaHeaderRender})
source_group("${SOURCE_GROUP_SOURCE_START}render" FILES ${ModVanillaSourceRender})
source_group("${SOURCE_GROUP_HEADER_START}block" FILES ${ModVanillaHeaderBlock})
source_group("${SOURCE_GROUP_SOURCE_START}block" FILES ${ModVanillaSourceBlock})
source_group("${SOURCE_GROUP_HEADER_START}manager" FILES ${ModVanillaHeaderManager})
source_group("${SOURCE_GROUP_SOURCE_START}manager" FILES ${ModVanillaSourceManager})
source_group("${SOURCE_GROUP_HEADER_START}world" FILES ${ModVanillaHeaderWorld})
source_group("${SOURCE_GROUP_SOURCE_START}world" FILES ${ModVanillaSourceWorld})

add_library(ModVanilla SHARED ${ModVanillaHeaders} ${ModVanillaSources} ${irs_resources})

use_base_library(ModVanilla ModBase)
use_base_library(ModVanilla CoreBase)
use_base_library(ModVanilla RenderBase)

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