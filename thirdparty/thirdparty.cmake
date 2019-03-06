cmake_minimum_required (VERSION 2.8)

include (${CMAKE_CURRENT_LIST_DIR}/boost/boost.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/SDL/sdl.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/steamaudio_api/steamaudio_api.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/Vulkan/vulkan.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/glm/glm.cmake)

add_subdirectory (${CMAKE_CURRENT_LIST_DIR}/zlib)
add_subdirectory (${CMAKE_CURRENT_LIST_DIR}/libpng)