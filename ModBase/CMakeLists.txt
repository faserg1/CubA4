cmake_minimum_required (VERSION 2.8)

set(ModBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(ModBaseIncludeDirBase ${ModBaseIncludeDir}/base)
set(ModBaseIncludeDirContainer ${ModBaseIncludeDir}/container)
set(ModBaseIncludeDirEntity ${ModBaseIncludeDir}/entity)
set(ModBaseIncludeDirWorld ${ModBaseIncludeDir}/world)

set(ModBaseHeaderBase 
	${ModBaseIncludeDirBase}/BaseManager.hpp
)
set(ModBaseHeaderContainer
	${ModBaseIncludeDirContainer}/BaseContainer.hpp
)	
set(ModBaseHeaderEntity
	${ModBaseIncludeDirEntity}/BaseEntity.hpp
)
set(ModBaseHeaderWorld
	${ModBaseIncludeDirWorld}/WorldManager.hpp
	${ModBaseIncludeDirWorld}/World.hpp
	${ModBaseIncludeDirWorld}/WorldSubscriber.hpp
)

#source_group("Header Files\\base" FILES ${ModBaseHeaderBase})
#source_group("Header Files\\container" FILES ${ModBaseHeaderContainer})
#source_group("Header Files\\entity" FILES ${ModBaseHeaderEntity})
#source_group("Header Files\\world" FILES ${ModBaseHeaderWorld})

set(ModBaseHeaders 
	${ModBaseIncludeDir}/ModExportHelper.hpp
	${ModBaseIncludeDir}/ModInfo.hpp
	${ModBaseHeaderBase}
	${ModBaseHeaderContainer}
	${ModBaseHeaderEntity}
	${ModBaseHeaderWorld}
)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})

set_target_properties(ModBaseProject PROPERTIES FOLDER "API")