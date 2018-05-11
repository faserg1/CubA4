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
	
	#Options
	
	def set_dry_run(self, dry_run):
		self._dry_run = dry_run
		
	def set_virtual_destructor(self, is_virtual):
		self._virtual_dtr = is_virtual
		
	def set_empty_constructor(self, is_empty):
		self._ctr_empty_realization = is_empty
	
	def set_empty_destructor(self, is_empty):
		self._dtr_empty_realization = is_empty
		
	def set_access_constructor(self, access):
		self._ctr_access = access
		
	def set_access_destructor(self, access):
		self._dtr_access = access
		
	#Generations
	
	def _generate_guard(self, file):
		name = self._get_name()
		upper_file_name = name.upper() + "_HPP"
		header_guard_starts = "#ifndef " + upper_file_name + "\n"
		header_guard_define = "#define " + upper_file_name + "\n"
		header_guard_ends = "#endif // " + upper_file_name + "\n"
		file.add_lines(header_guard_starts + header_guard_define, header_guard_ends, False, True)
		
	def _generate_namespaces(self, file):
		namespaces = self._get_namespaces()
		for namespace in namespaces:
			namespace_open = "namespace " + namespace + "\n{"
			namespace_close = "}"
			file.add_lines(namespace_open, namespace_close)
		
	def _generate_class_proto(self, file):
		name = self._get_name()
	
		class_define = "class " + name + "\n{\n"
		class_public = "public:\n"
		class_protected = "protected:\n"
		class_private = "private:\n"
		class_ends = "};"
		
		class_ctr = "\t" + "explicit " + name + "()" + (" {}" if self._ctr_empty_realization else ";") + "\n"
		class_dtr = "\t" + ("virtual " if self._virtual_dtr else "") + "~" + name + "()" + (" {}" if self._dtr_empty_realization else ";") + "\n"
		
		class_open = class_define + class_public
		if self._ctr_access == "public":
			class_open += class_ctr
		if self._dtr_access == "public":
			class_open += class_dtr
		
		class_open += class_protected
			
		if self._ctr_access == "protected":
			class_open += class_ctr
		if self._dtr_access == "protected":
			class_open += class_dtr
		
		class_open += class_private
		
		if self._ctr_access == "private":
			class_open += class_ctr
		if self._dtr_access == "private":
			class_open += class_dtr
		
		class_close = class_ends
		
		file.add_lines(class_open, class_close)
	
	#Getters
	
	def _get_namespaces(self):
		return copy.deepcopy(self._full_name[:-1])
		
	def _get_name(self):
		return self._full_name[-1]
	
	#Saver
	
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
	
	#Members
	
	_full_name = ""
	_module_name = ""
	_cwd = ""
	_dry_run = False
	_virtual_dtr = False
	_ctr_empty_realization = False
	_dtr_empty_realization = False
	_ctr_access = "public"
	_dtr_access = "public"