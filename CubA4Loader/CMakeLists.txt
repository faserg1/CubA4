cmake_minimum_required (VERSION 3.12)
set(CubA4LoaderSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE CubA4LoaderSources
    "${CubA4LoaderSourceDir}/**/*.hpp"
    "${CubA4LoaderSourceDir}/**/*.cpp"
    "${CubA4LoaderSourceDir}/*.hpp"
    "${CubA4LoaderSourceDir}/*.cpp"
)

source_group(TREE ${CubA4LoaderSourceDir} FILES ${CubA4LoaderSources})

link_directories(${STEAM_AUDIO_LIBRARY_DIR})

if (WIN32)
	set(OPTIONS WIN32)
endif ()

add_executable(CubA4Loader ${OPTIONS} ${CubA4LoaderSources})
target_compile_features(CubA4Loader PRIVATE ${TARGET_CXX_STD})
target_include_directories(CubA4Loader PRIVATE src)


#libs
use_base_library(CubA4Loader CoreBase)
use_base_library(CubA4Loader RenderBase)
use_base_library(CubA4Loader ModBase)

use_library(CubA4Loader Core)
use_library(CubA4Loader ModLoader)
use_library(CubA4Loader Network)

#thrid-party include directories
target_include_directories(CubA4Loader PRIVATE ${STEAM_AUDIO_INCLUDE_DIR})
#thridparty link libraries
target_link_libraries(CubA4Loader PRIVATE Boost::boost Boost::filesystem SDL2::SDL2 SDL2::SDL2main fmt::fmt)

#system libraries
use_system_loader_library(CubA4Loader)

if (WIN32)
	set (STEAM_AUDIO_DLL "${STEAM_AUDIO_BINARY_DIR}/phonon.dll")
	
	set_target_properties(
		CubA4Loader PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CUBA4_ROOT_RUNTIME_DIR}")
	
	add_custom_command(TARGET CubA4Loader POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${STEAM_AUDIO_DLL} ${COPY_DLL_OUTPUT_DIR}
	)
elseif(UNIX)
	set (STEAM_AUDIO_SO "${STEAM_AUDIO_LIBRARY_DIR}/libphonon.so")
	
	add_custom_command(TARGET CubA4Loader POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${STEAM_AUDIO_SO} ${COPY_SO_OUTPUT_DIR}
	)
endif (WIN32)

set_target_properties(CubA4Loader PROPERTIES FOLDER "Executables")

set_target_properties( CubA4Loader
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
	RUNTIME_OUTPUT_DIRECTORY "${BIN_BUILD_OUTPUT_DIRECTORY}/$<0:>"
)