#!/usr/bin/env python3

import copy
import os

class GeneratorBase:
	def __init__(self, full_name, module_name):
		self._cwd = os.getcwd()
		self._full_name = full_name
		self._module_name = module_name
	
	def _generate_guard(self, file):
		name = self._full_name[-1]
		upper_file_name = name.upper() + "_HPP"
		header_guard_starts = "#ifndef " + upper_file_name + "\n"
		header_guard_define = "#define " + upper_file_name + "\n"
		header_guard_ends = "#endif // " + upper_file_name + "\n"
		file.add_lines(header_guard_starts + header_guard_define, header_guard_ends, False, True)

	def _generate_namespaces(self, file):
		namespaces = copy.deepcopy(self._full_name)
		for namespace in namespaces:
			namespace_open = "namespace " + namespace + "\n{"
			namespace_close = "}"
			file.add_lines(namespace_open, namespace_close)
	
	_full_name = ""
	_module_name = ""
	_cwd = ""