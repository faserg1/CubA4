cmake_minimum_required (VERSION 3.12)

set(CoreIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(CoreSourceCacheDir ${CoreSourceDir}/cache)
set(CoreSourceResourcesDir ${CoreSourceDir}/resources)
set(CoreSourceFilesystemDir ${CoreSourceDir}/filesystem)
set(CoreSourceUtilDir ${CoreSourceDir}/util)
set(CoreSourceGameDir ${CoreSourceDir}/game)
set(CoreSourceWorldDir ${CoreSourceDir}/world)
set(CoreSourceSystemDir ${CoreSourceDir}/system)
set(CoreSourceLoggingDir ${CoreSourceDir}/logging)
set(CoreSourceConfigDir ${CoreSourceDir}/config)
set(CoreSourceCache
	${CoreSourceCacheDir}/CacheManager.cpp
	${CoreSourceCacheDir}/CacheResource.cpp
	${CoreSourceCacheDir}/Cache.cpp
)
set(CoreHeaderCache
	${CoreSourceCacheDir}/CacheManager.hpp
	${CoreSourceCacheDir}/CacheResource.hpp
	${CoreSourceCacheDir}/Cache.hpp
)
set(CoreSourceResources
	${CoreSourceResourcesDir}/Resource.cpp
	${CoreSourceResourcesDir}/Resources.cpp
	${CoreSourceResourcesDir}/ResourcesManager.cpp
)
set(CoreHeaderResources
	${CoreSourceResourcesDir}/Resource.hpp
	${CoreSourceResourcesDir}/Resources.hpp
	${CoreSourceResourcesDir}/ResourcesManager.hpp
)
set(CoreSourceFilesystem
	${CoreSourceFilesystemDir}/File.cpp
	${CoreSourceFilesystemDir}/Directory.cpp
)
set(CoreHeaderFilesystem
	${CoreSourceFilesystemDir}/File.hpp
	${CoreSourceFilesystemDir}/Directory.hpp
)
set(CoreHeaderUtil
	${CoreSourceUtilDir}/ChunkPosHash.hpp
)
set(CoreSourceGame
	${CoreSourceGameDir}/Game.cpp
)
set(CoreHeaderGame
	${CoreSourceGameDir}/Game.hpp
)
set(CoreSourceWorld
	${CoreSourceWorldDir}/World.cpp
	${CoreSourceWorldDir}/Chunk.cpp
	${CoreSourceWorldDir}/ChunkRange.cpp
	${CoreSourceWorldDir}/ChunkRangeBuilder.cpp
)
set(CoreHeaderWorld
	${CoreSourceWorldDir}/World.hpp
	${CoreSourceWorldDir}/Chunk.hpp
	${CoreSourceWorldDir}/ChunkRange.hpp
	${CoreSourceWorldDir}/ChunkRangeBuilder.hpp
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
	${CoreSourceSystemDir}/Startup.hpp
	${CoreSourceSystemDir}/Environment.hpp
	${CoreSourceSystemDir}/EnvironmentBuilder.hpp
	${CoreSourceSystemDir}/EnvironmentContext.hpp
	${CoreSourceSystemDir}/EnvironmentBuilderData.hpp
	${CoreSourceSystemDir}/EnvironmentBuilderContext.hpp
	${CoreSourceSystemDir}/IdentityMap.hpp
)
set(CoreSourceLogging
	${CoreSourceLoggingDir}/Logger.cpp
	${CoreSourceLoggingDir}/LoggerStreams.cpp
)
set(CoreHeaderLogging
	${CoreSourceLoggingDir}/Logger.hpp
	${CoreSourceLoggingDir}/LoggerStreams.hpp
)
set(CoreSourceConfig
	${CoreSourceConfigDir}/CoreConfig.cpp
	${CoreSourceConfigDir}/FilePaths.cpp
)
set(CoreHeaderConfig
	${CoreSourceConfigDir}/CoreConfig.hpp
	${CoreSourceConfigDir}/FilePaths.hpp
)

set(CoreHeaders
	${CoreIncludeDir}/Core.hpp
	${CoreHeaderLogging}
	${CoreHeaderConfig}
	${CoreHeaderSystem}
	${CoreHeaderWorld}
	${CoreHeaderGame}
	${CoreHeaderUtil}
	${CoreHeaderFilesystem}
	${CoreHeaderResources}
	${CoreHeaderCache}
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
	${CoreSourceFilesystem}
	${CoreSourceResources}
	${CoreSourceCache}
)
source_group("${SOURCE_GROUP_SOURCE_START}logging" FILES ${CoreSourceLogging})
source_group("${SOURCE_GROUP_SOURCE_START}config" FILES ${CoreSourceConfig})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreHeaderSystem})
source_group("${SOURCE_GROUP_SOURCE_START}system" FILES ${CoreSourceSystem})
source_group("${SOURCE_GROUP_HEADER_START}world" FILES ${CoreHeaderWorld})
source_group("${SOURCE_GROUP_SOURCE_START}world" FILES ${CoreSourceWorld})
source_group("${SOURCE_GROUP_HEADER_START}game" FILES ${CoreHeaderGame})
source_group("${SOURCE_GROUP_SOURCE_START}game" FILES ${CoreSourceGame})
source_group("${SOURCE_GROUP_HEADER_START}util" FILES ${CoreHeaderUtil})
source_group("${SOURCE_GROUP_HEADER_START}filesystem" FILES ${CoreHeaderFilesystem})
source_group("${SOURCE_GROUP_SOURCE_START}filesystem" FILES ${CoreSourceFilesystem})
source_group("${SOURCE_GROUP_HEADER_START}resources" FILES ${CoreHeaderResources})
source_group("${SOURCE_GROUP_SOURCE_START}resources" FILES ${CoreSourceResources})
source_group("${SOURCE_GROUP_HEADER_START}cache" FILES ${CoreHeaderCache})
source_group("${SOURCE_GROUP_SOURCE_START}cache" FILES ${CoreSourceCache})
	
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