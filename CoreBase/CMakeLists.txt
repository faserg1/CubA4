cmake_minimum_required (VERSION 3.12)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreBaseIncludeGameDir ${CoreBaseIncludeDir}/game)
set(CoreBaseIncludeExceptionsDir ${CoreBaseIncludeDir}/exceptions)
set(CoreBaseIncludeModelDir ${CoreBaseIncludeDir}/model)
set(CoreBaseIncludeSystemDir ${CoreBaseIncludeDir}/system)
set(CoreBaseIncludeInfoDir ${CoreBaseIncludeDir}/info)
set(CoreBaseIncludeConfigDir ${CoreBaseIncludeDir}/config)
set(CoreBaseIncludeLoggingDir ${CoreBaseIncludeDir}/logging)
set(CoreBaseHeaderGame
	${CoreBaseIncludeGameDir}/IGame.hpp
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

)
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreBaseHeaderConfig})

source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreBaseHeaderLogging})
source_group("${SOURCE_GROUP_HEADER_START}info" FILES ${CoreBaseHeaderInfo})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreBaseHeaderSystem})
source_group("${SOURCE_GROUP_HEADER_START}exceptions" FILES ${CoreBaseHeaderExceptions})
source_group("${SOURCE_GROUP_HEADER_START}model" FILES ${CoreBaseHeaderModel})
source_group("${SOURCE_GROUP_HEADER_START}game" FILES ${CoreBaseHeaderGame})

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")