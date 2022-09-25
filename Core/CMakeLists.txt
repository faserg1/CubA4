cmake_minimum_required (VERSION 3.12)

set(CoreIncludeDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(CoreSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE CoreSources
    "${CoreIncludeDir}/*.hpp"
    "${CoreIncludeDir}/**/*.hpp"
    "${CoreSourceDir}/**/*.hpp"
    "${CoreSourceDir}/**/*.cpp"
    "${CoreSourceDir}/*.hpp"
    "${CoreSourceDir}/*.cpp"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${CoreSources})

add_library(Core SHARED ${CoreSources})

target_compile_definitions(Core PRIVATE
    LOGURU_USE_FMTLIB=1
)

target_include_directories(Core INTERFACE include)

use_base_library(Core CoreBase)
use_base_library(Core ModBase)

#third-party library
target_include_directories(Core PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Core PRIVATE Boost::boost Boost::filesystem ${boost_stacktrace_lib})
target_link_libraries(Core PRIVATE logguru_win_lib)

if (UNIX)
    target_link_libraries(Core PRIVATE loguru)
endif()

#set output directory
set_target_properties(Core
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}"
)

set_target_properties(Core PROPERTIES FOLDER "Core")