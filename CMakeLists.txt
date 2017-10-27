cmake_minimum_required (VERSION 2.8)
project (CubA4 C CXX)

set (CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/build)

set(BUILD_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

#prepare config
include (Arch.cmake)

#first prepare thirdparty libraries
include (thirdparty/thirdparty.cmake)
#add_subdirectory (thirdparty)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH  ${BUILD_OUTPUT_DIRECTORY})
set(RUNTIME_OUTPUT_DIRECTORY  ${BUILD_OUTPUT_DIRECTORY})

if (WIN32)
	set (COPY_DLL_OUTPUT_DIR "${BUILD_OUTPUT_DIRECTORY}/$<CONFIG>/")
endif (WIN32)

#prepare interfaces
add_subdirectory (ModBase)
add_subdirectory (RenderBase)

#Standard mods
add_subdirectory (ModVanilla)

#prepare mod loader
add_subdirectory (ModLoader)

#executables
add_subdirectory (CubA4Loader)
add_subdirectory (CubA4Server)

#special
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubA4Loader)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY lib )
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib )