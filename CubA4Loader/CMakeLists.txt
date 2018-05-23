cmake_minimum_required (VERSION 2.8)
set(CubA4LoaderSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)
set(CubA4LoaderSourceAppDir ${CubA4LoaderSourceDir}/app)
set(CubA4LoaderSourceRenderDir ${CubA4LoaderSourceDir}/render)
set(CubA4LoaderSourceWindowDir ${CubA4LoaderSourceDir}/window)


set(CubA4LoaderSourceApp
	${CubA4LoaderSourceAppDir}/AppInfo.cpp
	${CubA4LoaderSourceAppDir}/CubA4Main.cpp
	${CubA4LoaderSourceAppDir}/AppVersion.cpp
)
set(CubA4LoaderHeaderApp
	${CubA4LoaderSourceAppDir}/AppInfo.hpp
	${CubA4LoaderSourceAppDir}/CubA4Main.hpp
	${CubA4LoaderSourceAppDir}/AppVersion.hpp
)

set(CubA4LoaderHeaderRender
	${CubA4LoaderSourceRenderDir}/RenderLoader.hpp
)
set(CubA4LoaderSourceRender
	${CubA4LoaderSourceRenderDir}/RenderLoader.cpp
)
set(CubA4LoaderHeaderWindow
	${CubA4LoaderSourceWindowDir}/Window.hpp
)
set(CubA4LoaderSourceWindow
	${CubA4LoaderSourceWindowDir}/Window.cpp
)
set(CubA4LoaderHeaders
	${CubA4LoaderSourceDir}/main.cpp
	${CubA4LoaderHeaderRender}
	${CubA4LoaderHeaderWindow}
	${CubA4LoaderHeaderApp}
)
set(CubA4LoaderSources 
	${CubA4LoaderSourceDir}/main.cpp
	${CubA4LoaderSourceRender}
	${CubA4LoaderSourceWindow}
	${CubA4LoaderSourceApp}
)

source_group("${SOURCE_GROUP_HEADER_START}render" FILES ${CubA4LoaderHeaderRender})
source_group("${SOURCE_GROUP_SOURCE_START}render" FILES ${CubA4LoaderSourceRender})
source_group("${SOURCE_GROUP_HEADER_START}app" FILES ${CubA4LoaderHeaderApp})
source_group("${SOURCE_GROUP_SOURCE_START}app" FILES ${CubA4LoaderSourceApp})
source_group("${SOURCE_GROUP_HEADER_START}window" FILES ${CubA4LoaderHeaderWindow})
source_group("${SOURCE_GROUP_SOURCE_START}window" FILES ${CubA4LoaderSourceWindow})

link_directories(
#third party
	${SDL_LIBRARY_DIR}
	${VULKAN_SDK_LIB}
	${STEAM_AUDIO_LIBRARY_DIR}
	${Boost_LIBRARY_DIRS})

add_executable(CubA4Loader ${CubA4LoaderHeaders} ${CubA4LoaderSources})

#libs
get_target_property(CORE_BASE_INCLUDE_DIRECTORIES CoreBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CubA4Loader PUBLIC ${CORE_BASE_INCLUDE_DIRECTORIES})

get_target_property(CORE_INCLUDE_DIRECTORIES Core INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CubA4Loader PRIVATE ${CORE_INCLUDE_DIRECTORIES})
target_link_libraries(CubA4Loader PRIVATE Core)

get_target_property(MOD_LOADER_INCLUDE_DIRECTORIES ModLoader INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CubA4Loader PRIVATE ${MOD_LOADER_INCLUDE_DIRECTORIES})
target_link_libraries(CubA4Loader PRIVATE ModLoader)

get_target_property(RENDER_BASE_INCLUDE_DIRECTORIES RenderBase INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CubA4Loader PUBLIC ${RENDER_BASE_INCLUDE_DIRECTORIES})

#find thrid-party libraries
find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2test PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)

find_library(phonon PATHS ${STEAM_AUDIO_LIBRARY_DIR} NO_DEFAULT_PATH)

#thrid-party include directories
target_include_directories(CubA4Loader PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(CubA4Loader PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(CubA4Loader PRIVATE ${STEAM_AUDIO_INCLUDE_DIR})

#thridparty link libraries
target_link_libraries(CubA4Loader PRIVATE SDL2 SDL2main phonon Boost::filesystem)

if (WIN32)
	set (SDL2_DLL "${SDL_LIBRARY_DIR}/SDL2.dll")
	set (STEAM_AUDIO_DLL "${STEAM_AUDIO_BINARY_DIR}/phonon.dll")
	
	set_target_properties(
		CubA4Loader PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CUBA4_ROOT_DIR}")
	
	add_custom_command(TARGET CubA4Loader POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${SDL2_DLL} ${COPY_DLL_OUTPUT_DIR}
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${STEAM_AUDIO_DLL} ${COPY_DLL_OUTPUT_DIR}
	)
endif (WIN32)

set_target_properties(CubA4Loader PROPERTIES FOLDER "Executables")