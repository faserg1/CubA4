cmake_minimum_required (VERSION 2.8)

link_directories(${SDL_LIBRARY_DIR} ${VULKAN_SDK_LIB})
add_executable(CubA4Loader ${PROJECT_SOURCE_DIR}/CubA4Loader/src/main.cpp)

#target_link_libraries (CubA4Loader INTERFACE ModBase)
#target_link_libraries (CubA4Loader INTERFACE RenderBase)

#target_link_libraries (CubA4Loader ModBase)
#target_link_libraries (CubA4Loader RenderBase)

find_library(SDL2 PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2main PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(SDL2test PATHS ${SDL_LIBRARY_DIR} NO_DEFAULT_PATH)

find_library(vulkan-1 PATHS ${VULKAN_SDK_LIB} NO_DEFAULT_PATH)

target_include_directories(CubA4Loader PRIVATE ${SDL_INCLUDE_DIR})
target_link_libraries(CubA4Loader PRIVATE SDL2 SDL2main vulkan-1)