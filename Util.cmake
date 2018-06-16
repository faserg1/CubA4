cmake_minimum_required (VERSION 2.8)

function(add_irs module_dir name)
	set (${irs_files}
		/gen/irs.hpp
		/gen/irs.cpp
		/gen/irs-headers.hpp
		/gen/irs-data.hpp)
		
	set(${add_irs} 1)
		
	foreach(irs_file ${irs_files})
		if(NOT EXISTS ${irs_file})
			set(${add_irs} 0)
		endif()
	endforeach(irs_file)
	
	if (${add_irs})
		set(${name}
			${module_dir}/gen/irs.hpp
			${module_dir}/gen/irs.cpp
			${module_dir}/gen/irs-headers.hpp
			${module_dir}/gen/irs-data.hpp
			PARENT_SCOPE
		)
	else()
		
	endif()
endfunction(add_irs)