cmake_minimum_required (VERSION 2.8)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModBaseIncludeDirBase ${ModBaseIncludeDir}/base)
set(ModBaseIncludeDirContainer ${ModBaseIncludeDir}/container)
set(ModBaseIncludeDirObject ${ModBaseIncludeDir}/object)
set(ModBaseIncludeDirWorld ${ModBaseIncludeDir}/world)

set(ModBaseHeaderBase 
	${ModBaseIncludeDirBase}/BaseManager.hpp
)
set(ModBaseHeaderContainer
	${ModBaseIncludeDirContainer}/BaseContainer.hpp
)	
set(ModBaseHeaderObject
	${ModBaseIncludeDirObject}/BaseObject.hpp
	${ModBaseIncludeDirObject}/BaseEntity.hpp
	${ModBaseIncludeDirObject}/BaseBlock.hpp
	${ModBaseIncludeDirObject}/BaseItem.hpp
)
set(ModBaseHeaderWorld
	${ModBaseIncludeDirWorld}/WorldProvider.hpp
	${ModBaseIncludeDirWorld}/World.hpp
	${ModBaseIncludeDirWorld}/WorldSubscriber.hpp
	${ModBaseIncludeDirWorld}/Chunk.hpp
)

if (MSVC)

source_group("Header Files\\base" FILES ${ModBaseHeaderBase})
source_group("Header Files\\container" FILES ${ModBaseHeaderContainer})
source_group("Header Files\\object" FILES ${ModBaseHeaderObject})
source_group("Header Files\\world" FILES ${ModBaseHeaderWorld})

endif(MSVC)

set(ModBaseHeaders 
	${ModBaseIncludeDir}/ModExportHelper.hpp
	${ModBaseIncludeDir}/ModInfo.hpp
	${ModBaseHeaderBase}
	${ModBaseHeaderContainer}
	${ModBaseHeaderObject}
	${ModBaseHeaderWorld}
)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")