set(STEAM_AUDIO_PATH ${CMAKE_CURRENT_LIST_DIR})

set(STEAM_AUDIO_INCLUDE_DIR ${STEAM_AUDIO_PATH}/include)

if (WIN32)
	set(STEAM_AUDIO_OS Windows)
elseif (UNIX)
	set(STEAM_AUDIO_OS Linux)
endif()

set (STEAM_AUDIO_LIBRARY_DIR ${STEAM_AUDIO_PATH}/lib/${STEAM_AUDIO_OS}/${TARGET_ARCH})
set (STEAM_AUDIO_BINARY_DIR ${STEAM_AUDIO_PATH}/bin/${STEAM_AUDIO_OS}/${TARGET_ARCH})

find_library(phonon PATHS ${STEAM_AUDIO_LIBRARY_DIR} NO_DEFAULT_PATH)