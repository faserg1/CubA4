cmake_minimum_required (VERSION 2.8)
set(ModVanillaIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModVanillaIncludeCoreDir ${ModVanillaIncludeDir}/core)
set(ModVanillaIncludeCoreInfoDir ${ModVanillaIncludeCoreDir}/info)

set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(ModVanillaSourceCoreDir ${ModVanillaSourceDir}/core)
set(ModVanillaSourceCoreInfoDir ${ModVanillaSourceCoreDir}/info)
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
	${ModVanillaHeader})
source_group("${SOURCE_GROUP_HEADER_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaHeaderCoreInfo})

set(ModVanillaSources 
	${ModVanillaSourceDir}/ModVanillaInfo.cpp
	${ModVanillaSourceDir}/ExportMod.cpp
	${ModVanillaSourceCoreInfo}
	${ModVanillaSource}
	)
source_group("${SOURCE_GROUP_SOURCE_START}core${SOURCE_GROUP_SEP}info" FILES ${ModVanillaSourceCoreInfo})
	
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