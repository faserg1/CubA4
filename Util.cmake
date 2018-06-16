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