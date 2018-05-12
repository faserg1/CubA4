#!/usr/bin/env python3

import os
import re
from .lineutil import *

RE_NC_P = "(?!^#)"
RE_BEGIN = re.compile(RE_NC_P + "cmake_minimum_required\\s*\\(VERSION.*\\)")

class CMakePatcher:
	def __init__(self, module_name, header_path, source_path):
		self._cmake_text = ""
		self._cwd = os.getcwd()
		self._module_name = module_name
		self._header_path = header_path
		self._source_path = source_path
		self._read()
	
	def patch(self):
		self._cmake_starts()
		self._insert_files(self._header_path)
		self._insert_files(self._source_path)
		if not self._dry_run:
			self._write()
		else:
			print("CMake not saved: dry run.")
			print(self._cmake_text)
		
	#Options
	
	def set_dry_run(self, dry_run):
		self._dry_run = dry_run
	
	#Helper functions
	
	def _cmake_starts(self):
		self._cmake_begin_index = self._find(RE_BEGIN)
		if self._cmake_begin_index < 0:
			self._insert(0, "cmake_minimum_required (VERSION 2.8)\n")
			self._cmake_begin_index = self._find(RE_BEGIN)
	
	def _convert_folders(self, folders):
		full_folders = ""
		for folder in folders:
			full_folders += "Source" if folder == "src" else camel_case(folder)
		return full_folders
		
	def _full_folders_name(self, folders):
		return self._module_name + self._convert_folders(folders) + "Dir"
	
	def _prev_folder_name(self, folders):
		if len(folders) > 1:
			return self._full_folders_name(folders[:-1])
		return "CMAKE_CURRENT_LIST_DIR"

	def _files_set_name(self, folders, set):
		#ignore "src" or "include" dirs
		return self._module_name + set + self._convert_folders(folders[1:])
	
	def _get_set_by_filename(self, filename):
		header_ends = [".h", ".hpp"]
		source_ends = [".c", ".cpp"]
		for header_end in header_ends:
			if filename.endswith(header_end):
				return "Header"
		for source_end in source_ends:
			if filename.endswith(source_end):
				return "Source"
		raise "Unknown set"
	
	#Search and paste functions
		
	def _folder(self, folders, index_after):
		full_name = self._full_folders_name(folders)
		pattern = RE_NC_P + "set\\s*\\(\\s*" + full_name + "\\s+.*\\)"
		re_folder = re.compile(pattern)
		index = self._find(re_folder)
		if index < 0:
			last_folder = folders[-1]
			last_folder_path = "${" + self._prev_folder_name(folders) + "}/" + last_folder
			self._insert(index_after, "set(" + full_name + " " + last_folder_path + ")")
			return self._find(re_folder)
		return index
	
	def _last_appearance(self, folders):
		folder_var = "\\${" + self._full_folders_name(folders) + "}"
		do_not_search_pattern = "(?!\\.h(pp)?)(?!\\.c(pp)?)"
		pattern = folder_var + "(\\w|/)+" + do_not_search_pattern + ".*\n*\\s*\\)"
		rc = re.compile(pattern)
		return last_appearance(self._cmake_text, rc)
		
	def _files(self, folders, set):
		files_set_name = self._files_set_name(folders, set)
		print(files_set_name)
	
	def _insert_files(self, file_path):
		folders_and_file = split_path(file_path)
		folders = folders_and_file[:-1]
		filename = folders_and_file[-1]
		index_after = self._cmake_begin_index
		path_folder = []
		for folder in folders:
			path_folder.append(folder)
			index_after = self._folder(path_folder, index_after)
		set = self._get_set_by_filename(filename)
		self._files(path_folder, set)
	
	def _cmake_path(self):
		return os.path.join(self._cwd, self._module_name, "CMakeLists.txt")
	
	def _read(self):
		cmake_path = self._cmake_path()
		with open(cmake_path, "r") as cmake_file:
			self._cmake_text = cmake_file.read()
			
	def _write(self):
		cmake_path = self._cmake_path()
		with open(cmake_path, "w") as cmake_file:
			cmake_file.write(self._cmake_text)
			
	def _find(self, pattern):
		return find_line_by_pattern(self._cmake_text, pattern)
		
	def _insert(self, index, text, on_new_line = True):
		if on_new_line:
			text = "\n" + text
		self._cmake_text = insert_text(self._cmake_text, text, index)
		return self._cmake_text
	
	_cmake_text = ""
	_module_name = ""
	_header_path = ""
	_source_path = ""
	_cwd = ""
	
	_dry_run = False
	
	_cmake_begin_index = 0