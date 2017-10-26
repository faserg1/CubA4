cmake_minimum_required (VERSION 2.8)

#include_directories(${SDL_INCLUDE_DIR})
link_directories(${SDL_LIBRARY_DIR})
add_executable(CubA4Loader ${PROJECT_SOURCE_DIR}/CubA4Loader/src/main.cpp)

#target_link_libraries (CubA4Loader INTERFACE ModBase)
#target_link_libraries (CubA4Loader INTERFACE RenderBase)

#target_link_libraries (CubA4Loader ModBase)
#target_link_libraries (CubA4Loader RenderBase)

find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2test PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)


target_include_directories(CubA4Loader PRIVATE ${SDL_INCLUDE_DIR})
target_link_libraries(CubA4Loader PRIVATE SDL2 SDL2main)

#target_include_directories(CubA4Loader PUBLIC $<INTERFACE_INCLUDE_DIRECTORIES:include>)

#target_include_directories(CubA4Loader INTERFACE ModBase)
#target_include_directories(CubA4Loader INTERFACE RenderBase)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubA4Loader)