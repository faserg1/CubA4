cmake_minimum_required (VERSION 2.8)

function(add_irs module_dir name)
	set(${name}
		${module_dir}/gen/irs.hpp
		${module_dir}/gen/irs.cpp
		${module_dir}/gen/irs-headers.hpp
		${module_dir}/gen/irs-data.hpp
		PARENT_SCOPE
	)
endfunction(add_irs)

function(use_base_library target source)
	get_target_property(BASE_INCLUDE_DIRECTORIES ${source} INTERFACE_INCLUDE_DIRECTORIES)
	target_include_directories(${target} PUBLIC ${BASE_INCLUDE_DIRECTORIES})
endfunction(use_base_library)

function(use_library target source)
	get_target_property(LIBRARY_INCLUDE_DIRECTORIES ${source} INTERFACE_INCLUDE_DIRECTORIES)
	target_include_directories(${target} PRIVATE ${LIBRARY_INCLUDE_DIRECTORIES})
	target_link_libraries(${target} PRIVATE ${source})
endfunction(use_library)

function(use_thread_library target)
	if (UNIX)
		target_link_libraries(${target} PRIVATE pthread)
	endif()
endfunction(use_thread_library)

function(use_system_loader_library target)
	if (UNIX)
		target_link_libraries(${target} PRIVATE dl)
	endif()
endfunction(use_system_loader_library)
