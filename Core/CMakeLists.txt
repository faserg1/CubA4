cmake_minimum_required (VERSION 3.12)

set(CoreIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreIncludeGameDir ${CoreIncludeDir}/game)
set(CoreIncludeWorldDir ${CoreIncludeDir}/world)
set(CoreIncludeSystemDir ${CoreIncludeDir}/system)
set(CoreIncludeLoggingDir ${CoreIncludeDir}/logging)
set(CoreIncludeConfigDir ${CoreIncludeDir}/config)
set(CoreSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(CoreSourceGameDir ${CoreSourceDir}/game)
set(CoreSourceWorldDir ${CoreSourceDir}/world)
set(CoreSourceSystemDir ${CoreSourceDir}/system)
set(CoreSourceLoggingDir ${CoreSourceDir}/logging)
set(CoreSourceConfigDir ${CoreSourceDir}/config)
set(CoreSourceGame
	${CoreSourceGameDir}/Game.cpp
)
set(CoreHeaderGame
	${CoreIncludeGameDir}/Game.hpp
)
set(CoreSourceWorld
	${CoreSourceWorldDir}/World.cpp
	${CoreSourceWorldDir}/Chunk.cpp
)
set(CoreHeaderWorld
	${CoreIncludeWorldDir}/World.hpp
	${CoreIncludeWorldDir}/Chunk.hpp
)
set(CoreSourceSystem
	${CoreSourceSystemDir}/Startup.cpp
	${CoreSourceSystemDir}/Environment.cpp
	${CoreSourceSystemDir}/EnvironmentBuilder.cpp
	${CoreSourceSystemDir}/EnvironmentContext.cpp
	${CoreSourceSystemDir}/EnvironmentBuilderData.cpp
	${CoreSourceSystemDir}/EnvironmentBuilderContext.cpp
	${CoreSourceSystemDir}/IdentityMap.cpp
)
set(CoreHeaderSystem
	${CoreIncludeSystemDir}/Startup.hpp
	${CoreIncludeSystemDir}/Environment.hpp
	${CoreIncludeSystemDir}/EnvironmentBuilder.hpp
	${CoreIncludeSystemDir}/EnvironmentContext.hpp
	${CoreIncludeSystemDir}/EnvironmentBuilderData.hpp
	${CoreIncludeSystemDir}/EnvironmentBuilderContext.hpp
	${CoreIncludeSystemDir}/IdentityMap.hpp
)
set(CoreSourceLogging
	${CoreSourceLoggingDir}/Logger.cpp
)
set(CoreHeaderLogging
	${CoreIncludeLoggingDir}/Logger.hpp
)
set(CoreSourceConfig
	${CoreSourceConfigDir}/CoreConfig.cpp
	${CoreSourceConfigDir}/FilePaths.cpp
)
set(CoreHeaderConfig
	${CoreIncludeConfigDir}/CoreConfig.hpp
	${CoreIncludeConfigDir}/FilePaths.hpp
)

set(CoreHeaders
	${CoreIncludeDir}/Core.hpp
	${CoreHeaderLogging}
	${CoreHeaderConfig}
	${CoreHeaderSystem}
	${CoreHeaderWorld}
	${CoreHeaderGame}
)
source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreHeaderLogging})
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreHeaderConfig})

set(CoreSources
	${CoreSourceDir}/Core.cpp
	${CoreSourceLogging}
	${CoreSourceConfig}
	${CoreSourceSystem}
	${CoreSourceWorld}
	${CoreSourceGame}
)
source_group("${SOURCE_GROUP_SOURCE_START}logging" FILES ${CoreSourceLogging})
source_group("${SOURCE_GROUP_SOURCE_START}config" FILES ${CoreSourceConfig})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreHeaderSystem})
source_group("${SOURCE_GROUP_SOURCE_START}system" FILES ${CoreSourceSystem})
source_group("${SOURCE_GROUP_HEADER_START}world" FILES ${CoreHeaderWorld})
source_group("${SOURCE_GROUP_SOURCE_START}world" FILES ${CoreSourceWorld})
source_group("${SOURCE_GROUP_HEADER_START}game" FILES ${CoreHeaderGame})
source_group("${SOURCE_GROUP_SOURCE_START}game" FILES ${CoreSourceGame})
	
add_library(Core SHARED ${CoreHeaders} ${CoreSources})
target_include_directories(Core INTERFACE include)

use_base_library(Core CoreBase)
use_base_library(Core ModBase)

#third-party library
target_include_directories(Core PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Core PRIVATE Boost::filesystem ${boost_stacktrace_lib})

#set output directory
set_target_properties(Core
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(Core PROPERTIES FOLDER "Core")