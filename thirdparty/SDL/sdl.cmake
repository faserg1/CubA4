cmake_minimum_required (VERSION 2.8)
if (MSVC)
	set(SDL2_PATH ${CMAKE_CURRENT_LIST_DIR}/msvc)
endif (MSVC)

set (SDL_INCLUDE_DIR ${SDL2_PATH}/include  )
set (SDL_LIBRARY_DIR ${SDL2_PATH}/lib/${TARGET_ARCH})