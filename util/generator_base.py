#!/usr/bin/env python3

import copy
import os
import subprocess

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
	
	#Class
	
	def set_virtual_destructor(self, is_virtual):
		self._virtual_dtr = is_virtual
		
	def set_empty_constructor(self, is_empty):
		self._ctr_empty_realization = is_empty
	
	def set_empty_destructor(self, is_empty):
		self._dtr_empty_realization = is_empty
		
	def _generate_class_proto(self, file):
		name = self._get_name()
	
		header_class_define = "class " + name + "\n{\n"
		header_class_public = "public:\n"
		header_class_protected = "protected:\n"
		header_class_private = "private:\n"
		header_class_ends = "};"
		
		header_class_ctr = "\t" + "explicit " + name + "()" + ("{}" if self._ctr_empty_realization else ";") + "\n"
		header_class_dtr = "\t" + ("virtual " if self._virtual_dtr else "") + "~" + name + "()" + ("{}" if self._dtr_empty_realization else ";") + "\n"
	
	#Base
	
	def _write_file(self, file, file_path):
		str = file.to_string()
		with open(file_path, "w") as file_handle:
			file_handle.write(str)
	
	def _save_to(self, file, ext, folder):
		root_folder = os.path.join(self._cwd, self._module_name, folder)
		namespaces = self._get_namespaces()
		if namespaces[0] == "CubA4":
			namespaces = namespaces[1:]
		put_to_folder = os.path.join(root_folder, *namespaces)
		if not os.path.exists(put_to_folder):
			print("Creating directory \"" + put_to_folder + "\"")
			if not self._dry_run:
				os.makedirs(put_to_folder)
		file_path = os.path.join(put_to_folder, self._get_name() + ext)
		print("Creating file \"" + file_path + "\"")
		if not self._dry_run:
			self._write_file(file, file_path)
			self._add_to_git(file_path)

	def _save_to_include(self, file, ext):
		self._save_to(file, ext, "include")
		
	def _save_to_src(self, file, ext):
		self._save_to(file, ext, "src")
		
	def _add_to_git(self, file_path):
		subprocess.call(["git", "add", file_path])
	
	_full_name = ""
	_module_name = ""
	_cwd = ""
	_dry_run = False
	_virtual_dtr = False
	_ctr_empty_realization = False
	_dtr_empty_realization = False
	_ctr_access = "public"
	_dtr_access = "public"