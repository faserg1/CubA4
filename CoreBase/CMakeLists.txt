cmake_minimum_required (VERSION 2.8)

set(CoreBaseIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreBaseIncludeConfigDir ${CoreBaseIncludeDir}/config)
set(CoreBaseIncludeLoggingDir ${CoreBaseIncludeDir}/logging)
set(CoreBaseHeaderConfig
	${CoreBaseIncludeConfigDir}/IFilePaths.hpp
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
	${CoreBaseIncludeDir}/ICoreConfig.hpp
	${CoreBaseHeaderConfig}
)
source_group("${SOURCE_GROUP_HEADER_START}config" FILES ${CoreBaseHeaderConfig})

source_group("${SOURCE_GROUP_HEADER_START}logging" FILES ${CoreBaseHeaderLogging})

add_library(CoreBase INTERFACE)
target_include_directories(CoreBase INTERFACE include)

#Visibility for IDE
add_custom_target(CoreBaseProject SOURCES ${CoreBaseHeaders})

set_target_properties(CoreBaseProject PROPERTIES FOLDER "API")