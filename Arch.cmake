cmake_minimum_required (VERSION 2.8)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set (TARGET_ARCH x64 )
else ()
	set (TARGET_ARCH x86 )
endif ()

if (MSVC)
	set(SOURCE_GROUP_SEP "\\")
	set(SOURCE_GROUP_HEADER_START "Header Files\\")
	set(SOURCE_GROUP_SOURCE_START "Source Files\\")
else()
	set(SOURCE_GROUP_SEP "/")
	set(SOURCE_GROUP_HEADER_START "")
	set(SOURCE_GROUP_SOURCE_START "")
endif ()

if ( CMAKE_COMPILER_IS_GNUCC )
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4275")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCUBA4_DEBUG")
