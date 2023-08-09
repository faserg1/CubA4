compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/block.vert ${SHADERS_OUT_FOLDER}/block.vert.spv vert)
compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/block.frag ${SHADERS_OUT_FOLDER}/block.frag.spv frag)

compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/plane.vert ${SHADERS_OUT_FOLDER}/plane.vert.spv vert)
compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/plane.frag ${SHADERS_OUT_FOLDER}/plane.frag.spv frag)

compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/debug.vert ${SHADERS_OUT_FOLDER}/debug.vert.spv vert)
compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/debug.frag ${SHADERS_OUT_FOLDER}/debug.frag.spv frag)

compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/entity.vert ${SHADERS_OUT_FOLDER}/entity.vert.spv vert)
compileShader(RenderVulkan ${SHADERS_IN_FOLDER}/entity.frag ${SHADERS_OUT_FOLDER}/entity.frag.spv frag)
