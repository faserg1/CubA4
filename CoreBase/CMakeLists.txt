cmake_minimum_required (VERSION 3.12)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreBaseIncludeFilesystemDir ${CoreBaseIncludeDir}/filesystem)
set(CoreBaseIncludeCacheDir ${CoreBaseIncludeDir}/cache)
set(CoreBaseIncludeResourcesDir ${CoreBaseIncludeDir}/resources)
set(CoreBaseIncludeUtilDir ${CoreBaseIncludeDir}/util)
set(CoreBaseIncludeGameDir ${CoreBaseIncludeDir}/game)
set(CoreBaseIncludeExceptionsDir ${CoreBaseIncludeDir}/exceptions)
set(CoreBaseIncludeModelDir ${CoreBaseIncludeDir}/model)
set(CoreBaseIncludeSystemDir ${CoreBaseIncludeDir}/system)
set(CoreBaseIncludeInfoDir ${CoreBaseIncludeDir}/info)
set(CoreBaseIncludeConfigDir ${CoreBaseIncludeDir}/config)
set(CoreBaseIncludeLoggingDir ${CoreBaseIncludeDir}/logging)
set(CoreBaseHeaderFilesystem
	${CoreBaseIncludeFilesystemDir}/IAbstractResource.hpp
	${CoreBaseIncludeFilesystemDir}/IAbstractDirectory.hpp
)
set(CoreBaseHeaderCache
	${CoreBaseIncludeCacheDir}/ICacheManager.hpp
	${CoreBaseIncludeCacheDir}/ICache.hpp
	${CoreBaseIncludeCacheDir}/ICacheResource.hpp
	${CoreBaseIncludeCacheDir}/CacheType.hpp
)
set(CoreBaseHeaderResources
	${CoreBaseIncludeResourcesDir}/IResourcesManager.hpp
	${CoreBaseIncludeResourcesDir}/IResources.hpp
	${CoreBaseIncludeResourcesDir}/IResource.hpp
	${CoreBaseIncludeResourcesDir}/ResourcesType.hpp
)
set(CoreBaseHeaderUtil
	${CoreBaseIncludeUtilDir}/ISubscription.hpp
	${CoreBaseIncludeUtilDir}/SubscriptionHelper.hpp
)
set(CoreBaseHeaderGame
	${CoreBaseIncludeGameDir}/IGame.hpp
	${CoreBaseIncludeGameDir}/IGameSubscriber.hpp
)

set(CoreBaseHeaderExceptions
	${CoreBaseIncludeExceptionsDir}/ICoreConfigException.hpp
	${CoreBaseIncludeExceptionsDir}/ICoreException.hpp
	${CoreBaseIncludeExceptionsDir}/ICoreLoggingException.hpp
)
set(CoreBaseHeaderModel
	${CoreBaseIncludeModelDir}/IModelDefinition.hpp
	${CoreBaseIncludeModelDir}/IShapeModelDefinition.hpp
	${CoreBaseIncludeModelDir}/IRenderModelDefinition.hpp
	${CoreBaseIncludeModelDir}/ICollisionModelDefinition.hpp

)
set(CoreBaseHeaderSystem
	${CoreBaseIncludeSystemDir}/IStartup.hpp
	${CoreBaseIncludeSystemDir}/IAppCallback.hpp
	${CoreBaseIncludeSystemDir}/IEnvironment.hpp
	${CoreBaseIncludeSystemDir}/IEnvironmentBuilder.hpp
	${CoreBaseIncludeSystemDir}/IIdentityiMap.hpp
)
set(CoreBaseHeaderInfo
	${CoreBaseIncludeInfoDir}/IApplicationInfo.hpp
	${CoreBaseIncludeInfoDir}/IVersion.hpp
	${CoreBaseIncludeInfoDir}/IVersionDependency.hpp
)
set(CoreBaseHeaderConfig
	${CoreBaseIncludeConfigDir}/IFilePaths.hpp
	${CoreBaseIncludeConfigDir}/ICoreConfig.hpp
)

set(CoreBaseHeaderLogging
	${CoreBaseIncludeLoggingDir}/LogCommon.hpp
	${CoreBaseIncludeLoggingDir}/ILoggerTagged.hpp
	${CoreBaseIncludeLoggingDir}/ILogger.hpp
)

set(CoreBaseHeaders
	${CoreBaseHeaderLogging}
	${CoreBaseIncludeDir}/CoreExportHelper.hpp
	${CoreBaseIncludeDir}/ICore.hpp
	${CoreBaseHeaderConfig}
	${CoreBaseHeaderInfo}
	${CoreBaseHeaderSystem}
	${CoreBaseHeaderExceptions}
	${CoreBaseHeaderModel}
	${CoreBaseHeaderGame}
	${CoreBaseHeaderUtil}
	${CoreBaseHeaderResources}
	${CoreBaseHeaderCache}
	${CoreBaseHeaderFilesystem}

)
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreBaseHeaderConfig})

source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreBaseHeaderLogging})
source_group("${SOURCE_GROUP_HEADER_START}info" FILES ${CoreBaseHeaderInfo})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreBaseHeaderSystem})
source_group("${SOURCE_GROUP_HEADER_START}exceptions" FILES ${CoreBaseHeaderExceptions})
source_group("${SOURCE_GROUP_HEADER_START}model" FILES ${CoreBaseHeaderModel})
source_group("${SOURCE_GROUP_HEADER_START}game" FILES ${CoreBaseHeaderGame})
source_group("${SOURCE_GROUP_HEADER_START}util" FILES ${CoreBaseHeaderUtil})
source_group("${SOURCE_GROUP_HEADER_START}resources" FILES ${CoreBaseHeaderResources})
source_group("${SOURCE_GROUP_HEADER_START}cache" FILES ${CoreBaseHeaderCache})
source_group("${SOURCE_GROUP_HEADER_START}filesystem" FILES ${CoreBaseHeaderFilesystem})

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")