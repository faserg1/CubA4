cmake_minimum_required (VERSION 2.8)
if (MSVC)
	set(SDL2_PATH ${CMAKE_CURRENT_LIST_DIR}/msvc)
endif (MSVC)

set (SDL_INCLUDE_DIR ${SDL2_PATH}/include  )
set (SDL_LIBRARY_DIR ${SDL2_PATH}/lib/${TARGET_ARCH})

#add_library( SDL2 SHARED IMPORTED )
#add_library( SDL2main SHARED IMPORTED )
#add_library( SDL2test SHARED IMPORTED )
#set_target_properties( SDL2 PROPERTIES IMPORTED_LOCATION ${SDL_LIBRARY_DIR} )
#set_target_properties( SDL2main PROPERTIES IMPORTED_LOCATION ${SDL_LIBRARY_DIR} )
#set_target_properties( SDL2test PROPERTIES IMPORTED_LOCATION ${SDL_LIBRARY_DIR} )