cmake_minimum_required (VERSION 2.8)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

#Used boost version: 1_65_1

#set(BOOST_PATH ${CMAKE_CURRENT_LIST_DIR})

#set (BOOST_INCLUDE_DIR ${BOOST_PATH}/include )

find_package(Boost 1.65.0 REQUIRED
 COMPONENTS filesystem
 )