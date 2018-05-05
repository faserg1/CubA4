cmake_minimum_required (VERSION 2.8)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)

set(CoreBaseHeaders
	${CoreBaseIncludeDir}/CoreExportHelper.hpp
	${CoreBaseIncludeDir}/CoreBase.hpp
	${CoreBaseIncludeDir}/CoreConfigBase.hpp
	)

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")