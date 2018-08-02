cmake_minimum_required (VERSION 2.8)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

if (MSVC)
	set(boost_stacktrace_name stacktrace_windbg)
	set(boost_stacktrace_lib Boost::stacktrace_windbg)
else()
	
endif ()

find_package(Boost 1.67 EXACT REQUIRED
 COMPONENTS filesystem ${boost_stacktrace_name}
 )