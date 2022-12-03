cmake_minimum_required (VERSION 3.12)
set(CubA4LauncherSourceDir ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE CubA4LauncherSources
    "${CubA4LauncherSourceDir}/**/*.hpp"
    "${CubA4LauncherSourceDir}/**/*.cpp"
    "${CubA4LauncherSourceDir}/*.hpp"
    "${CubA4LauncherSourceDir}/*.cpp"
)

if (WIN32)
	set(OPTIONS WIN32)
endif ()

add_executable(CubA4Launcher ${OPTIONS} ${CubA4LauncherSources})
target_include_directories(CubA4Launcher PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_include_directories(CubA4Launcher PRIVATE src)
target_link_libraries(CubA4Launcher PRIVATE ${wxWidgets_LIBRARIES})


set_target_properties(CubA4Launcher PROPERTIES FOLDER "Executables")

set_target_properties( CubA4Launcher
    PROPERTIES
    BUILD_OUTPUT_DIRECTORY "${CUBA4_ROOT_RUNTIME_DIR}/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${CUBA4_ROOT_RUNTIME_DIR}/$<0:>"
	RUNTIME_OUTPUT_DIRECTORY "${CUBA4_ROOT_RUNTIME_DIR}/$<0:>"
)

