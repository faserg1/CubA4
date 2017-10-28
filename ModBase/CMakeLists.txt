cmake_minimum_required (VERSION 2.8)

set(ModBaseHeaders 
	${PROJECT_SOURCE_DIR}/ModBase/include/ModInfo.hpp)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)

#Visibility for IDE
add_custom_target(ModBaseProject SOURCES ${ModBaseHeaders})