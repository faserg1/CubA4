cmake_minimum_required (VERSION 3.12)
project (CubA4 CXX)

set (CMAKE_CXX_STANDARD 14)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#temporary for linux
set(CMAKE_BUILD_TYPE Debug)

#prepare config
include (Arch.cmake)
include (Util.cmake)

set(CUBA4_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/built/${TARGET_ARCH})

set(BIN_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/bin)
set(MOD_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/mods)
set(RENDER_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/render)

set(BUILD_OUTPUT_DIRECTORY ${BIN_BUILD_OUTPUT_DIRECTORY})

#first prepare thirdparty libraries
include (thirdparty/thirdparty.cmake)
#add_subdirectory (thirdparty)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH  ${BUILD_OUTPUT_DIRECTORY})
set(RUNTIME_OUTPUT_DIRECTORY  ${BUILD_OUTPUT_DIRECTORY})

if (WIN32)
	set (COPY_DLL_OUTPUT_DIR "${BUILD_OUTPUT_DIRECTORY}/$<CONFIG>/")
elseif(UNIX)
	set (COPY_SO_OUTPUT_DIR "${BUILD_OUTPUT_DIRECTORY}/")
endif ()

#prepare interfaces
add_subdirectory (CoreBase)
add_subdirectory (ModBase)
add_subdirectory (RenderBase)

#core
add_subdirectory (Core)
add_subdirectory (Network)

#Standard mods
add_subdirectory (ModVanilla)

#prepare mod loader
add_subdirectory (ModLoader)

#prepare renderer
add_subdirectory (RenderVulkan)

#executables
add_subdirectory (CubA4Loader)
add_subdirectory (CubA4Server)

#deps
add_dependencies(CubA4Loader Core Network ModLoader RenderVulkan ModVanilla)
add_dependencies(CubA4Server Core Network ModLoader ModVanilla)

#special
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubA4Loader)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY lib )
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib )

# Windows Generate batch file (parent folder):
#@echo off
#set MY_FUCKING_PATH=%CD%
#set BOOST_ROOT=D:\Libs\boost_1_67_0
#
#cd CubA4
#
#if not exist build mkdir build
#cd build
#
#if not exist x32 mkdir x32
#cd x32
#cmake -G "Visual Studio 15 2017" ../..
#cd ..
#
#if not exist x64 mkdir x64
#cd x64
#cmake -G "Visual Studio 15 2017 Win64" ../..
#cd ..
#
#cd %MY_FUCKING_PATH%
