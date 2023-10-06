#!/usr/bin/env python3

from .resource_generator import ResourceGenerator

projects = ["RenderVulkan", "Mods/ModVanilla"]

for project in projects:
	rg = ResourceGenerator(project)
	rg.generate()
