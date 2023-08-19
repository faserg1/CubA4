set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

if (MSVC)
	set(boost_stacktrace_name stacktrace_windbg)
	set(boost_stacktrace_lib Boost::stacktrace_windbg)
else()
	
endif ()

find_package(Boost 1.78.0 REQUIRED
	COMPONENTS ${boost_stacktrace_name} filesystem
)

find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")