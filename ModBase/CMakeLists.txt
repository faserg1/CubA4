cmake_minimum_required (VERSION 2.8)

set(ModBaseHeaders 
	include/ModInfo.hpp)
	
#target_include_directories(ModBase ...)
#install(TARGETS moduleA ...)

add_library(ModBase INTERFACE)
target_include_directories(ModBase INTERFACE include)
target_sources(ModBase INTERFACE ${ModBaseHeaders})
#target_include_directories(ModBase INTERFACE include/*.hpp)