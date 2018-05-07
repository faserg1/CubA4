cmake_minimum_required (VERSION 2.8)

link_directories(
#third party
	${SDL_LIBRARY_DIR}
	${VULKAN_SDK_LIB}
	${STEAM_AUDIO_LIBRARY_DIR}
	${Boost_LIBRARY_DIRS})

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src) 

set(CubA4LoaderRenderDir ${SOURCE_DIR}/render)
set(CubA4LoaderAppDir ${SOURCE_DIR}/app)
set(CubA4LoaderWindowDir ${SOURCE_DIR}/window)

set(CubA4LoaderRenderSources
	${CubA4LoaderRenderDir}/RenderLoader.hpp
	${CubA4LoaderRenderDir}/RenderLoader.cpp
)
set(CubA4LoaderAppSources
	${CubA4LoaderAppDir}/CubA4Main.hpp
	${CubA4LoaderAppDir}/CubA4Main.cpp
)
set(CubA4LoaderWindowSources
	${CubA4LoaderWindowDir}/Window.hpp
	${CubA4LoaderWindowDir}/Window.cpp
)

set(CubA4LoaderSources 
	${SOURCE_DIR}/main.cpp
	${CubA4LoaderRenderSources}
	${CubA4LoaderAppSources}
	${CubA4LoaderWindowSources}
)

if (MSVC)

source_group("Header Files\\render" FILES ${CubA4LoaderRenderSources})
source_group("Header Files\\app" FILES ${CubA4LoaderAppSources})
source_group("Header Files\\window" FILES ${CubA4LoaderWindowSources})

endif(MSVC)
	
add_executable(CubA4Loader ${CubA4LoaderSources})

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