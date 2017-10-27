cmake_minimum_required (VERSION 2.8)

set(ModVanillaHeaders 
	${PROJECT_SOURCE_DIR}/ModVanilla/src/ModVanilla.hpp)

set(ModVanillaSources 
	${PROJECT_SOURCE_DIR}/ModVanilla/src/ModVanilla.cpp)
	
add_library(ModVanilla SHARED ${ModVanillaHeaders} ${ModVanillaSources})
#target_include_directories(ModVanilla PUBLIC include/...)