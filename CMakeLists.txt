cmake_minimum_required (VERSION 3.12)
project (CubA4 C CXX)

set(TARGET_CXX_STD cxx_std_23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CUBA4_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

#prepare config
include (cmake/Arch.cmake)
include (cmake/Util.cmake)
include (cmake/ProjectPaths.cmake)

#first prepare thirdparty libraries
include (thirdparty/thirdparty.cmake)
#add_subdirectory (thirdparty)

if (WIN32)
	set (COPY_DLL_OUTPUT_DIR "${BUILD_OUTPUT_DIRECTORY}/")
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
add_subdirectory (Mods)

#prepare mod loader
add_subdirectory (ModLoader)

#prepare renderer
add_subdirectory (RenderVulkan)

#executables
add_subdirectory (CubA4Loader)
add_subdirectory (CubA4Server)
add_subdirectory (CubA4Launcher)

#deps
add_dependencies(CubA4Loader Core Network ModLoader RenderVulkan ModVanilla)
add_dependencies(CubA4Server Core Network ModLoader ModVanilla)

#special
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubA4Loader)
