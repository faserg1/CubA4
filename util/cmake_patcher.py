#!/usr/bin/env python3

import os

class CMakePatcher:
	def __init__(self, module_name, header_path, source_path):
		self._readed_cmake = ""
		self._cwd = os.getcwd()
		self._module_name = module_name
		self._header_path = header_path
		self._source_path = source_path
		self._read()
	
	def patch(self):
		pass
	
	def _read(self):
		cmake_path = os.path.join(self._cwd, self._module_name, "CMakeLists.txt")
		with open(cmake_path, "r") as cmake_file:
			self._readed_cmake = cmake_file.read()
	
	_readed_cmake = ""
	_module_name = ""
	_header_path = ""
	_source_path = ""
	_cwd = ""