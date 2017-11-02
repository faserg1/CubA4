cmake_minimum_required (VERSION 2.8)

set(ModVanillaSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(ModVanillaHeaders 
	${ModVanillaSourceDir}/ModVanilla.hpp)

set(ModVanillaSources 
	${ModVanillaSourceDir}/ModVanilla.cpp
	${ModVanillaSourceDir}/ExportMod.cpp
	)
	
add_library(ModVanilla SHARED ${ModVanillaHeaders} ${ModVanillaSources})
#target_include_directories(ModVanilla PUBLIC include/...)

get_target_property(MOD_BASE_INCLUDE_DIRECTORIES ModBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ModVanilla PUBLIC ${MOD_BASE_INCLUDE_DIRECTORIES})

#set output directory
set_target_properties( ModVanilla
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${MOD_BUILD_OUTPUT_DIRECTORY}"
)