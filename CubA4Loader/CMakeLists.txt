cmake_minimum_required (VERSION 2.8)

add_executable(CubA4Loader src/main.cpp)

#target_link_libraries (CubA4Loader INTERFACE ModBase)
#target_link_libraries (CubA4Loader INTERFACE RenderBase)

target_link_libraries (CubA4Loader ModBase)
target_link_libraries (CubA4Loader RenderBase)

#target_include_directories(CubA4Loader PUBLIC $<INTERFACE_INCLUDE_DIRECTORIES:include>)

#target_include_directories(CubA4Loader INTERFACE ModBase)
#target_include_directories(CubA4Loader INTERFACE RenderBase)