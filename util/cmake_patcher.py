#!/usr/bin/env python3

import os
import re
from .lineutil import *

RE_NC_P = "(?!^#)"
RE_BEGIN = re.compile(RE_NC_P + "cmake_minimum_required\\s*\\(VERSION.*\\)")

class CMakePatcher:
	def __init__(self, module_name, header_path, source_path):
		self._readed_cmake = ""
		self._cwd = os.getcwd()
		self._module_name = module_name
		self._header_path = header_path
		self._source_path = source_path
		self._read()
	
	def patch(self):
		self._cmake_starts()
		#self._root_folders()
	
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
	
	def _folder(self, folders, index_after):
		full_name = self._full_folders_name(folders)
		re_folder = re.compile(RE_NC_P + "set\\s*\\(\\s*" + full_name + "\\s+.*/\\)")
		index = self._find(re_folder)
		if index < 0:
			last_folder = folders[-1]
			last_folder_path = "${" + self._prev_folder_name(folders) + "}/" + last_folder
			self._insert(index_after, "set(" + full_name + " " + last_folder_path + ")")
			return self._find(re_folder)
		return index
	
	def _read(self):
		cmake_path = os.path.join(self._cwd, self._module_name, "CMakeLists.txt")
		with open(cmake_path, "r") as cmake_file:
			self._readed_cmake = cmake_file.read()
			
	def _find(self, pattern):
		return find_line_by_pattern(self._readed_cmake, pattern)
		
	def _insert(self, index, text):
		self._readed_cmake = insert_text(self._readed_cmake, text, index)
		return self._readed_cmake
	
	_readed_cmake = ""
	_module_name = ""
	_header_path = ""
	_source_path = ""
	_cwd = ""
	
	_cmake_begin_index = 0