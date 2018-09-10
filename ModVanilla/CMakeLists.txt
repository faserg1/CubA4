cmake_minimum_required (VERSION 3.12)
set(ModVanillaIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModVanillaIncludeCoreDir ${ModVanillaIncludeDir}/core)
set(ModVanillaIncludeCoreInfoDir ${ModVanillaIncludeCoreDir}/info)

set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(ModVanillaSourceStartupDir ${ModVanillaSourceDir}/startup)
set(ModVanillaSourceCoreDir ${ModVanillaSourceDir}/core)
set(ModVanillaSourceCoreInfoDir ${ModVanillaSourceCoreDir}/info)
set(ModVanillaSourceStartup
	${ModVanillaSourceStartupDir}/RenderStartup.cpp
)
set(ModVanillaHeaderStartup
	${ModVanillaSourceStartupDir}/RenderStartup.hpp
)
set(ModVanillaSource
	${ModVanillaSourceDir}/ModVanilla.cpp
)
set(ModVanillaHeader
	${ModVanillaIncludeDir}/ModVanilla.hpp
)
set(ModVanillaSourceCoreInfo
	${ModVanillaSourceCoreInfoDir}/Version.cpp
	${ModVanillaSourceCoreInfoDir}/VersionDependency.cpp
)
set(ModVanillaHeaderCoreInfo
	${ModVanillaIncludeCoreInfoDir}/Version.hpp
	${ModVanillaIncludeCoreInfoDir}/VersionDependency.hpp
)

set(ModVanillaHeaders 
	${ModVanillaSourceDir}/ModVanillaInfo.hpp
	${ModVanillaHeaderCoreInfo}
	${ModVanillaHeader}
	${ModVanillaHeaderStartup})
source_group("${SOURCE_GROUP_HEADER_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaHeaderCoreInfo})

set(ModVanillaSources 
	${ModVanillaSourceDir}/ModVanillaInfo.cpp
	${ModVanillaSourceDir}/ExportMod.cpp
	${ModVanillaSourceCoreInfo}
	${ModVanillaSource}
	${ModVanillaSourceStartup}
	)
source_group("${SOURCE_GROUP_SOURCE_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaSourceCoreInfo})
source_group("${SOURCE_GROUP_HEADER_START}startup" FILES ${ModVanillaHeaderStartup})
source_group("${SOURCE_GROUP_SOURCE_START}startup" FILES ${ModVanillaSourceStartup})

add_irs(${CMAKE_CURRENT_LIST_DIR} irs_resources)
source_group("resources" FILES ${irs_resources})

add_library(ModVanilla SHARED ${ModVanillaHeaders} ${ModVanillaSources} ${irs_resources})

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