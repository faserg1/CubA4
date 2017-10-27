cmake_minimum_required (VERSION 2.8)

link_directories(${SDL_LIBRARY_DIR} ${VULKAN_SDK_LIB} ${STEAM_AUDIO_LIBRARY_DIR})
add_executable(CubA4Loader ${PROJECT_SOURCE_DIR}/CubA4Loader/src/main.cpp)

#target_link_libraries (CubA4Loader INTERFACE ModBase)
#target_link_libraries (CubA4Loader INTERFACE RenderBase)

#target_link_libraries (CubA4Loader ModBase)
#target_link_libraries (CubA4Loader RenderBase)

find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2test PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)

find_library(vulkan-1 PATHS ${VULKAN_SDK_LIB} NO_DEFAULT_PATH)

find_library(phonon PATHS ${STEAM_AUDIO_LIBRARY_DIR} NO_DEFAULT_PATH)

target_include_directories(CubA4Loader PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(CubA4Loader PRIVATE ${STEAM_AUDIO_INCLUDE_DIR})
target_include_directories(CubA4Loader PRIVATE ${VULKAN_SDK_INCLUDE})


target_link_libraries(CubA4Loader PRIVATE SDL2 SDL2main vulkan-1 phonon)

if (WIN32)
	set (SDL2_DLL "${SDL_LIBRARY_DIR}/SDL2.dll")
	set (STEAM_AUDIO_DLL "${STEAM_AUDIO_BINARY_DIR}/phonon.dll")
	
	add_custom_command(TARGET CubA4Loader POST_BUILD
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${SDL2_DLL} ${COPY_DLL_OUTPUT_DIR}
	   COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${STEAM_AUDIO_DLL} ${COPY_DLL_OUTPUT_DIR}
	)
endif (WIN32)

