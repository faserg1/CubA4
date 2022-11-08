#!/usr/bin/env python3

class CoreDefaults:
	@classmethod
	def get_header_folder(cls):
		return "src"

class ModVanillaDefaults:
	@classmethod
	def get_header_folder(cls):
		return "src"

class RenderVulkanDefaults:
	@classmethod
	def get_header_folder(cls):
		return "src"

class Defaults:
	_modules = {"Core": CoreDefaults}
	_modules = {"ModVanilla": ModVanillaDefaults}
	_modules = {"RenderVulkan": RenderVulkanDefaults}

	@classmethod
	def get_header_folder(cls, module: str):
		if module in cls._modules:
			defaults = cls._modules[module]
			func = getattr(defaults, "get_header_folder", None)
			if func:
				return func()
		return "include"

	@classmethod
	def get_src_folder(cls, module: str):
		if module in cls._modules:
			defaults = cls._modules[module]
			func = getattr(defaults, "get_src_folder", None)
			if func:
				return func()
		return "src"