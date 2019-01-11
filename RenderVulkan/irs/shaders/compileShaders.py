#!/usr/bin/env python3

import os
import subprocess

VULKAN_SDK_PATH = os.environ["VULKAN_SDK"]
VULKAN_SDK_BIN = os.path.join(VULKAN_SDK_PATH, "bin")
SPIR_V_COMPILER = os.path.join(VULKAN_SDK_BIN, "spirv-as")
SPIR_V_VALIDATOR = os.path.join(VULKAN_SDK_BIN, "spirv-val")

shaders = ["default.vert.spv", "default.frag.spv"]
for shader in shaders:
	shader_in = os.path.join("sources", shader)
	shader_out = os.path.join("compiled", shader)
	print("Compiling", shader_in)
	subprocess.run([SPIR_V_COMPILER, shader_in, "-o", shader_out])
	print("Validating", shader_in)
	subprocess.run([SPIR_V_VALIDATOR, shader_out])