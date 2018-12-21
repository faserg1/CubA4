cmake_minimum_required (VERSION 3.12)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModBaseIncludeManagerDir ${ModBaseIncludeDir}/manager)
set(ModBaseIncludeContainerDir ${ModBaseIncludeDir}/container)
set(ModBaseIncludeExceptionDir ${ModBaseIncludeDir}/exception)
set(ModBaseIncludeModDir ${ModBaseIncludeDir}/mod)
set(ModBaseIncludeObjectDir ${ModBaseIncludeDir}/object)
set(ModBaseIncludeWorldDir ${ModBaseIncludeDir}/world)
set(ModBaseHeaderManager
	${ModBaseIncludeManagerDir}/IModManager.hpp
	${ModBaseIncludeManagerDir}/IModRenderManager.hpp
	${ModBaseIncludeManagerDir}/IModBlockManager.hpp
	${ModBaseIncludeManagerDir}/IModItemManager.hpp
)
set(ModBaseHeaderContainer
	${ModBaseIncludeContainerDir}/IContainer.hpp
)
set(ModBaseHeaderException
	${ModBaseIncludeExceptionDir}/IModException.hpp
	${ModBaseIncludeExceptionDir}/IModLoadException.hpp
	${ModBaseIncludeExceptionDir}/IModRuntimeException.hpp
)
set(ModBaseHeaderMod
	${ModBaseIncludeModDir}/IModLoader.hpp
	${ModBaseIncludeModDir}/IMod.hpp
	${ModBaseIncludeModDir}/IModLinker.hpp
)
set(ModBaseHeaderObject
	${ModBaseIncludeObjectDir}/IObject.hpp
	${ModBaseIncludeObjectDir}/IEntity.hpp
	${ModBaseIncludeObjectDir}/IBlock.hpp
	${ModBaseIncludeObjectDir}/IItem.hpp
)
set(ModBaseHeaderWorld
	${ModBaseIncludeWorldDir}/IWorld.hpp
	${ModBaseIncludeWorldDir}/IWorldSubscriber.hpp
	${ModBaseIncludeWorldDir}/IChunk.hpp
	${ModBaseIncludeWorldDir}/IChunkRange.hpp
	${ModBaseIncludeWorldDir}/IWorldDefinition.hpp
	${ModBaseIncludeWorldDir}/IWorldGenerator.hpp
	${ModBaseIncludeWorldDir}/Position.hpp
	${ModBaseIncludeWorldDir}/IChunkRange.hpp
)
set(ModBaseHeaders 
	${ModBaseIncludeDir}/ModExportHelper.hpp
	${ModBaseIncludeDir}/IModInfo.hpp
	${ModBaseHeaderBase}
	${ModBaseHeaderContainer}
	${ModBaseHeaderException}
	${ModBaseHeaderMod}
	${ModBaseHeaderObject}
	${ModBaseHeaderWorld}
	${ModBaseHeaderManager}
)

source_group("${SOURCE_GROUP_HEADER_START}container" FILES ${ModBaseHeaderContainer})
source_group("${SOURCE_GROUP_HEADER_START}exception" FILES ${ModBaseHeaderException})
source_group("${SOURCE_GROUP_HEADER_START}mod" FILES ${ModBaseHeaderMod})
source_group("${SOURCE_GROUP_HEADER_START}object" FILES ${ModBaseHeaderObject})
source_group("${SOURCE_GROUP_HEADER_START}world" FILES ${ModBaseHeaderWorld})
source_group("${SOURCE_GROUP_HEADER_START}manager" FILES ${ModBaseHeaderManager})

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")