#!/usr/bin/env python3

import os
import copy

class ResourceFinder:
	def __init__(self, module_name):
		self._cwd = os.getcwd()
		self._module_name = module_name
		self._files = []
		
	def find_all(self):
		resources_folder = os.path.join(self._cwd, self._module_name, "irs")
		if not os.path.exists(resources_folder) or not os.path.isdir(resources_folder):
			return
		for root, dirs, files in os.walk(resources_folder):
			self._files.extend([os.path.relpath(os.path.join(root, file), resources_folder) for file in files])
			
	def get_files(self):
		return copy.copy(self._files)
	
	_cwd = ""
	_module_name = ""
	_files = []