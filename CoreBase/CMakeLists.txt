cmake_minimum_required (VERSION 3.12)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
<<<<<<< HEAD
set(CoreBaseIncludeExceptionsDir ${CoreBaseIncludeDir}/exceptions)
=======
set(CoreBaseIncludeModelDir ${CoreBaseIncludeDir}/model)
>>>>>>> aa36a9f74d88b3d0f3f99d107e1a616ca14bace7
set(CoreBaseIncludeSystemDir ${CoreBaseIncludeDir}/system)
set(CoreBaseIncludeInfoDir ${CoreBaseIncludeDir}/info)
set(CoreBaseIncludeConfigDir ${CoreBaseIncludeDir}/config)
set(CoreBaseIncludeLoggingDir ${CoreBaseIncludeDir}/logging)
<<<<<<< HEAD
set(CoreBaseHeaderExceptions
	${CoreBaseIncludeExceptionsDir}/ICoreException.hpp
	${CoreBaseIncludeExceptionsDir}/ICoreConfigException.hpp
	${CoreBaseIncludeExceptionsDir}/ICoreException.hpp
	${CoreBaseIncludeExceptionsDir}/ICoreLoggingException.hpp
=======
set(CoreBaseHeaderModel
	${CoreBaseIncludeModelDir}/IModel.hpp
	${CoreBaseIncludeModelDir}/IShapeModel.hpp
	${CoreBaseIncludeModelDir}/IRenderModel.hpp
	${CoreBaseIncludeModelDir}/ICollisionModel.hpp
>>>>>>> aa36a9f74d88b3d0f3f99d107e1a616ca14bace7
)
set(CoreBaseHeaderSystem
	${CoreBaseIncludeSystemDir}/IStartup.hpp
	${CoreBaseIncludeSystemDir}/IAppCallback.hpp
	${CoreBaseIncludeSystemDir}/IEnvironment.hpp
	${CoreBaseIncludeSystemDir}/IEnvironmentBuilder.hpp
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
<<<<<<< HEAD
	${CoreBaseHeaderExceptions}
=======
	${CoreBaseHeaderModel}
>>>>>>> aa36a9f74d88b3d0f3f99d107e1a616ca14bace7
)
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreBaseHeaderConfig})

source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreBaseHeaderLogging})
source_group("${SOURCE_GROUP_HEADER_START}info" FILES ${CoreBaseHeaderInfo})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreBaseHeaderSystem})
<<<<<<< HEAD
source_group("${SOURCE_GROUP_HEADER_START}exceptions" FILES ${CoreBaseHeaderExceptions})
=======
source_group("${SOURCE_GROUP_HEADER_START}model" FILES ${CoreBaseHeaderModel})
>>>>>>> aa36a9f74d88b3d0f3f99d107e1a616ca14bace7

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")