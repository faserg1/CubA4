#!/usr/bin/env python3

class GeneratorBase:
	def __init__(self, module_name):
		self._cwd = os.getcwd()
		self._module_name = module_name
	
	_module_name = ""
	_cwd = ""