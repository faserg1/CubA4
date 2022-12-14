find_program(GLSL_COMPILER glslangValidator)

#Stages are vert, tesc, tese, geom, frag, or comp
function (compileShader TARGET SHADER_IN SHADER_OUT STAGE)
	string(RANDOM LENGTH 12 TARGET_HASH)
	set(CUSTOM_TARGET_NAME ${TARGET}_${TARGET_HASH})
	add_custom_target(${CUSTOM_TARGET_NAME}
		DEPENDS ${SHADER_IN}
		BYPRODUCTS ${SHADER_OUT}
		COMMAND ${GLSL_COMPILER} -V -S ${STAGE} -e main -o ${SHADER_OUT} ${SHADER_IN}
		SOURCES ${SHADER_IN}
	)
	add_dependencies(${TARGET} ${CUSTOM_TARGET_NAME})
	add_dependencies(ASSETS_GENERATION ${CUSTOM_TARGET_NAME})
endfunction()