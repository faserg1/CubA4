cmake_minimum_required (VERSION 2.8)

set (VULKAN_SDK_INCLUDE $ENV{VULKAN_SDK}/Include)

if (TARGET_ARCH STREQUAL x86)
	set (VULKAN_SDK_LIB $ENV{VULKAN_SDK}/Lib32 )
else ()
	set (VULKAN_SDK_LIB $ENV{VULKAN_SDK}/Lib )
endif ()

