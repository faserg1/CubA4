#!/usr/bin/env python3

import copy
import os

class GeneratorBase:
	def __init__(self, full_name, module_name):
		self._cwd = os.getcwd()
		self._full_name = full_name
		self._module_name = module_name
		self._dry_run = False
	
	def set_dry_run(self, dry_run):
		self._dry_run = dry_run
	
	def _generate_guard(self, file):
		name = self._get_name()
		upper_file_name = name.upper() + "_HPP"
		header_guard_starts = "#ifndef " + upper_file_name + "\n"
		header_guard_define = "#define " + upper_file_name + "\n"
		header_guard_ends = "#endif // " + upper_file_name + "\n"
		file.add_lines(header_guard_starts + header_guard_define, header_guard_ends, False, True)

	def _get_namespaces(self):
		return copy.deepcopy(self._full_name[:-1])
		
	def _get_name(self):
		return self._full_name[-1]
		
	def _generate_namespaces(self, file):
		namespaces = self._get_namespaces()
		for namespace in namespaces:
			namespace_open = "namespace " + namespace + "\n{"
			namespace_close = "}"
			file.add_lines(namespace_open, namespace_close)
	
	def _save_to(self, file, ext, folder):
		str = file.to_string()
		root_folder = os.path.join(self._cwd, self._module_name, folder)
		namespaces = self._get_namespaces()
		if namespaces[0] == "CubA4":
			namespaces = namespaces[1:]
		put_to_folder = os.path.join(root_folder, *namespaces)
		file_path = os.path.join(put_to_folder, self._get_name() + ext)
		if not os.path.exists(put_to_folder):
			print("Creating directory \"" + put_to_folder + "\"")
			if not self._dry_run:
				os.makedirs(put_to_folder)
		if not self._dry_run:
			pass
		self._add_to_git(file_path)

	def _save_to_include(self, file, ext):
		self._save_to(file, ext, "include")
		
	def _save_to_src(self, file, ext):
		self._save_to(file, ext, "src")
		
	def _add_to_git(self, file_path):
		print(file_path)
	
	_full_name = ""
	_module_name = ""
	_cwd = ""
	_dry_run = False