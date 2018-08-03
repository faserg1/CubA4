cmake_minimum_required (VERSION 3.12)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModBaseIncludeBaseDir ${ModBaseIncludeDir}/base)
set(ModBaseIncludeContainerDir ${ModBaseIncludeDir}/container)
set(ModBaseIncludeExceptionDir ${ModBaseIncludeDir}/exception)
set(ModBaseIncludeModDir ${ModBaseIncludeDir}/mod)
set(ModBaseIncludeObjectDir ${ModBaseIncludeDir}/object)
set(ModBaseIncludeWorldDir ${ModBaseIncludeDir}/world)

set(ModBaseHeaderBase 
	${ModBaseIncludeBaseDir}/IManager.hpp
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
	${ModBaseIncludeWorldDir}/IWorldProvider.hpp
	${ModBaseIncludeWorldDir}/IWorld.hpp
	${ModBaseIncludeWorldDir}/IWorldSubscriber.hpp
	${ModBaseIncludeWorldDir}/IChunk.hpp
)

source_group("${SOURCE_GROUP_HEADER_START}base" FILES ${ModBaseHeaderBase})
source_group("${SOURCE_GROUP_HEADER_START}container" FILES ${ModBaseHeaderContainer})
source_group("${SOURCE_GROUP_HEADER_START}exception" FILES ${ModBaseHeaderException})
source_group("${SOURCE_GROUP_HEADER_START}mod" FILES ${ModBaseHeaderMod})
source_group("${SOURCE_GROUP_HEADER_START}object" FILES ${ModBaseHeaderObject})
source_group("${SOURCE_GROUP_HEADER_START}world" FILES ${ModBaseHeaderWorld})

set(ModBaseHeaders 
	${ModBaseIncludeDir}/ModExportHelper.hpp
	${ModBaseIncludeDir}/IModInfo.hpp
	${ModBaseHeaderBase}
	${ModBaseHeaderContainer}
	${ModBaseHeaderException}
	${ModBaseHeaderMod}
	${ModBaseHeaderObject}
	${ModBaseHeaderWorld}
)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")