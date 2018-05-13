cmake_minimum_required (VERSION 2.8)

set(CoreIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreIncludeLoggingDir ${CoreIncludeDir}/logging)
set(CoreSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(CoreSourceLoggingDir ${CoreSourceDir}/logging)
set(CoreSourceLogging
	${CoreSourceLoggingDir}/Logger.cpp
)
set(CoreHeaderLogging
	${CoreIncludeLoggingDir}/Logger.hpp
)

set(CoreHeaders
	${CoreIncludeDir}/CoreConfig.hpp
	${CoreIncludeDir}/Core.hpp
	${CoreHeaderLogging}
)
source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreHeaderLogging})

set(CoreSources
	${CoreSourceDir}/CoreConfig.cpp 
	${CoreSourceDir}/Core.cpp
	${CoreSourceLogging}
)
source_group("${SOURCE_GROUP_SOURCE_START}logging" FILES ${CoreSourceLogging})
	
add_library(Core SHARED ${CoreHeaders} ${CoreSources})
target_include_directories(Core INTERFACE include)
#target_include_directories(Core PUBLIC include/...)

get_target_property(CORE_BASE_INCLUDE_DIRECTORIES CoreBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Core PUBLIC ${CORE_BASE_INCLUDE_DIRECTORIES})

#third-party library
target_include_directories(Core PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Core PRIVATE Boost::filesystem)

#set output directory
set_target_properties(Core
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(Core PROPERTIES FOLDER "Core")