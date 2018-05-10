cmake_minimum_required (VERSION 2.8)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModBaseIncludeDirBase ${ModBaseIncludeDir}/base)
set(ModBaseIncludeDirContainer ${ModBaseIncludeDir}/container)
set(ModBaseIncludeDirMod ${ModBaseIncludeDir}/mod)
set(ModBaseIncludeDirObject ${ModBaseIncludeDir}/object)
set(ModBaseIncludeDirWorld ${ModBaseIncludeDir}/world)

set(ModBaseHeaderBase 
	${ModBaseIncludeDirBase}/IManager.hpp
)
set(ModBaseHeaderContainer
	${ModBaseIncludeDirContainer}/IContainer.hpp
)
set(ModBaseHeaderMod
	${ModBaseIncludeDirMod}/IModLoader.hpp
	${ModBaseIncludeDirMod}/IMod.hpp
)
set(ModBaseHeaderObject
	${ModBaseIncludeDirObject}/IObject.hpp
	${ModBaseIncludeDirObject}/IEntity.hpp
	${ModBaseIncludeDirObject}/IBlock.hpp
	${ModBaseIncludeDirObject}/IItem.hpp
)
set(ModBaseHeaderWorld
	${ModBaseIncludeDirWorld}/IWorldProvider.hpp
	${ModBaseIncludeDirWorld}/IWorld.hpp
	${ModBaseIncludeDirWorld}/IWorldSubscriber.hpp
	${ModBaseIncludeDirWorld}/IChunk.hpp
)

if (MSVC)

source_group("Header Files\\base" FILES ${ModBaseHeaderBase})
source_group("Header Files\\container" FILES ${ModBaseHeaderContainer})
source_group("Header Files\\mod" FILES ${ModBaseHeaderMod})
source_group("Header Files\\object" FILES ${ModBaseHeaderObject})
source_group("Header Files\\world" FILES ${ModBaseHeaderWorld})

endif(MSVC)

set(ModBaseHeaders 
	${ModBaseIncludeDir}/ModExportHelper.hpp
	${ModBaseIncludeDir}/IModInfo.hpp
	${ModBaseHeaderBase}
	${ModBaseHeaderContainer}
	${ModBaseHeaderMod}
	${ModBaseHeaderObject}
	${ModBaseHeaderWorld}
)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")