cmake_minimum_required (VERSION 2.8)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreBaseIncludeSystemDir ${CoreBaseIncludeDir}/system)
set(CoreBaseIncludeInfoDir ${CoreBaseIncludeDir}/info)
set(CoreBaseIncludeConfigDir ${CoreBaseIncludeDir}/config)
set(CoreBaseIncludeLoggingDir ${CoreBaseIncludeDir}/logging)
set(CoreBaseIncludeUtilDir ${CoreBaseIncludeDir}/util)
set(CoreBaseHeaderSystem
	${CoreBaseIncludeSystemDir}/IStartup.hpp
	${CoreBaseIncludeSystemDir}/IAppCallback.hpp
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

set(CoreBaseHeaderUtil
	${CoreBaseIncludeUtilDir}/stringutil.hpp
)

set(CoreBaseHeaders
	${CoreBaseHeaderLogging}
	${CoreBaseIncludeDir}/CoreExportHelper.hpp
	${CoreBaseIncludeDir}/ICore.hpp
	${CoreBaseHeaderConfig}
	${CoreBaseHeaderInfo}
	${CoreBaseHeaderSystem}
	${CoreBaseHeaderUtil}
)
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreBaseHeaderConfig})

source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreBaseHeaderLogging})
source_group("${SOURCE_GROUP_HEADER_START}info" FILES ${CoreBaseHeaderInfo})
source_group("${SOURCE_GROUP_HEADER_START}system" FILES ${CoreBaseHeaderSystem})
source_group("${SOURCE_GROUP_HEADER_START}util" FILES ${CoreBaseHeaderUtil})

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")