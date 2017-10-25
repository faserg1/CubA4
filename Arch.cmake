cmake_minimum_required (VERSION 2.8)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set (TARGET_ARCH x64 )
else ()
	set (TARGET_ARCH x86 )
endif ()