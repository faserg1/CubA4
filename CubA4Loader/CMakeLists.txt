cmake_minimum_required (VERSION 3.12)
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
use_base_library(CubA4Loader CoreBase)
use_base_library(CubA4Loader RenderBase)
use_base_library(CubA4Loader ModBase)

use_library(CubA4Loader Core)
use_library(CubA4Loader ModLoader)
use_library(CubA4Loader Network)

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
message(${SDL2})
message(${SDL2main})
message(${SDL2test})
#system libraries
use_system_loader_library(CubA4Loader)

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
elseif(UNIX)
	set (SDL2_SO "${SDL_LIBRARY_DIR}/libSDL2.so")
	set (STEAM_AUDIO_SO "${STEAM_AUDIO_LIBRARY_DIR}/libphonon.so")
	
	add_custom_command(TARGET CubA4Loader POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${SDL2_SO} ${COPY_SO_OUTPUT_DIR}
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${STEAM_AUDIO_SO} ${COPY_SO_OUTPUT_DIR}
	   #COMMAND "${CMAKE_COMMAND}" -E create_symlink ${COPY_SO_OUTPUT_DIR}/{SDL2_SO} ${COPY_SO_OUTPUT_DIR}/${SDL2}
	)
endif (WIN32)

set_target_properties(CubA4Loader PROPERTIES FOLDER "Executables")