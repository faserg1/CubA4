cmake_minimum_required (VERSION 2.8)
project (CubA4 C CXX)

set (CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#prepare config
include (Arch.cmake)

#first prepare thirdparty libraries
include (thirdparty/thirdparty.cmake)
#add_subdirectory (thirdparty)

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