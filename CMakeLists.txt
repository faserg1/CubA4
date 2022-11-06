cmake_minimum_required (VERSION 3.12)
project (CubA4 C CXX)

set(TARGET_CXX_STD cxx_std_23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CUBA4_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

#prepare config
include (cmake/Arch.cmake)
include (cmake/Util.cmake)

set(CUBA4_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/built/${TARGET_ARCH})

set(BIN_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/bin)
set(MOD_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/mods)
set(RENDER_BUILD_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/render)
set(RESOURCES_OUTPUT_DIRECTORY ${CUBA4_ROOT_DIR}/data)

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
