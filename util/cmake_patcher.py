#!/usr/bin/env python3

import os
import re
from .lineutil import *

#CMakefile: ignore comments in regex (pattern)
RE_NC_P = "(?!^#)"
#CMakefile: start with set (pattern)
RE_SET_P = "set\\s*\\(\\s*"
#CMakefile: end of cmake expression (pattern)
RE_END_P = "(.|\n)*?\\)"
#CMakefile: start with source group
RE_SG_P = "source_group\\s*\\(\\s*"
RE_SG_SEP = "${SOURCE_GROUP_SEP}"
RE_SG_HS = "${SOURCE_GROUP_HEADER_START}"
RE_SG_SS = "${SOURCE_GROUP_SOURCE_START}"
#CMakefile: begin of the file
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
		if self._header_path:
			self._insert_files(self._header_path)
		if self._source_path:
			self._insert_files(self._source_path)
		if not self._dry_run:
			self._write()
		
	#Options
	
	def set_dry_run(self, dry_run):
		self._dry_run = dry_run
	
	#Helper functions
	
	def _cmake_starts(self):
		find_result = self._find(RE_BEGIN)
		if not find_result:
			self._insert(0, "cmake_minimum_required (VERSION 2.8)\n")
			find_result = self._find(RE_BEGIN).end
		self._cmake_begin_index = find_result.end
	
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
	
	def _get_set_by_filename(self, filename, plural = False):
		header_ends = [".h", ".hpp"]
		source_ends = [".c", ".cpp"]
		for header_end in header_ends:
			if filename.endswith(header_end):
				return "Header" + ("s" if plural else "")
		for source_end in source_ends:
			if filename.endswith(source_end):
				return "Source" + ("s" if plural else "")
		raise "Unknown set"
	
	def _files_set_name_by_path(self, file_path):
		folders_and_file = split_path(file_path)
		folders = folders_and_file[:-1]
		filename = folders_and_file[-1]
		set = self._get_set_by_filename(filename)
		return self._files_set_name(folders, set)
	
	def _index_before_end_to_insert(self, result):
		index_back_shift = 0
		for index in range(result.start, result.end)[::-1]:
			index_back_shift += 1
			symb = self._cmake_text[index]
			if symb == ")" or symb == "\n":
				continue
			elif not symb.isspace():
				index_back_shift -= 1
				break
		return result.end - index_back_shift
	
	def _dtir(self, result):
		print(self._cmake_text[result.start:result.end])
	
	#Search and paste functions
		
	def _folder(self, folders, index_after):
		full_name = self._full_folders_name(folders)
		pattern = RE_NC_P + RE_SET_P + full_name + "\\s+.*\\)"
		re_folder = re.compile(pattern)
		result = self._find(re_folder)
		if not result:
			last_folder = folders[-1]
			last_folder_path = "${" + self._prev_folder_name(folders) + "}/" + last_folder
			self._insert(index_after, "set(" + full_name + " " + last_folder_path + ")")
			return self._find(re_folder).end
		return result.end
	
	def _last_dir(self):
		pattern = RE_NC_P + RE_SET_P + self._module_name + "\\w+" + "Dir.+\\)"
		rc = re.compile(pattern)
		result = self._last_appearance(rc)
		if not result:
			return 0
		return result.end
		
	def _last_source_group(self):
		pattern = RE_NC_P + RE_SG_P + RE_END_P
		rc = re.compile(pattern)
		result = self._last_appearance(rc)
		if not result:
			return 0
		return result.end
	
	def _file_set(self, folders, set, index_after):
		files_set_name = self._files_set_name(folders, set)
		pattern = RE_NC_P + RE_SET_P + files_set_name + "\\s" + RE_END_P
		rc = re.compile(pattern)
		result = self._last_appearance(rc)
		if not result:
			set_start = "set(" + files_set_name
			index_insert = self._insert(index_after, set_start)
			self._insert(index_insert, ")")
			return index_insert
		return self._index_before_end_to_insert(result)
	
	def _add_folders(self, file_path):
		folders_and_file = split_path(file_path)
		folders = folders_and_file[:-1]
		index_after = self._cmake_begin_index
		path_folder = []
		for folder in folders:
			path_folder.append(folder)
			index_after = self._folder(path_folder, index_after)
		return index_after, path_folder
		
	def _add_files(self, file_path, index_after, path_folder):
		filename = split_path(file_path)[-1]
		set = self._get_set_by_filename(filename)
		index_to_insert_files = self._file_set(path_folder, set, index_after)
		folder_path = "${" + self._full_folders_name(path_folder) + "}"
		file_path_insert = folder_path + "/" + filename
		self._insert(index_to_insert_files, "\t" + file_path_insert)
		
	def _register_files(self, file_path):
		filename = split_path(file_path)[-1]
		set_reg = self._get_set_by_filename(filename, True)
		pattern = RE_NC_P + RE_SET_P + self._module_name + set_reg + RE_END_P
		rc = re.compile(pattern)
		result = self._last_appearance(rc)
		if not result:
			print(pattern)
			raise "Adding sets is not implemented yet"
		#check if set exists
		sub = self._cmake_text[result.start:result.end]
		files_set_name_var = "${" + self._files_set_name_by_path(file_path) + "}"
		if files_set_name_var in sub:
			#exists, do nothing
			return result.end
		else:
			#not exists, need to add
			index_insert = self._index_before_end_to_insert(result) 
			index_now = self._insert(index_insert, "\t" + files_set_name_var)
			length = index_now - index_insert
			return result.end + length
		
	def _add_source_group(self, file_path, index_after):
		folders_and_file = split_path(file_path)
		folders = folders_and_file[1:-1]
		filename = folders_and_file[-1]
		set = self._get_set_by_filename(filename)
		sg_set = RE_SG_HS if set == "Header" else RE_SG_SS
		pattern = RE_NC_P + RE_SG_P
		source_group_path = var_to_pattern(sg_set)
		for folder in folders[:-1]:
			source_group_path += folder + var_to_pattern(RE_SG_SEP)
		if not len(folders):
			return
		source_group_path += folders[-1]
		pattern += "\"?" + source_group_path + "\"?"
		rc = re.compile(pattern)
		result = self._last_appearance(rc)
		if result:
			#Adding in root, no need to add source group
			return
		index_last_group = self._last_source_group()
		if index_last_group > index_after:
			index_after = index_last_group
		sg = "source_group(\"" + sg_set
		for folder in folders[:-1]:
			sg += folder + RE_SG_SEP
		files_set_name_var = "${" + self._files_set_name_by_path(file_path) + "}"
		sg += folders[-1] + "\" FILES " + files_set_name_var + ")"
		self._insert(index_after, sg)
	
	def _insert_files(self, file_path):
		#add folders
		index_after, path_folder = self._add_folders(file_path)
		#check place for files
		index_all_dirs = self._last_dir()
		if index_all_dirs > index_after:
			index_after = index_all_dirs
		#add files
		self._add_files(file_path, index_after, path_folder)
		#register files
		index_after = self._register_files(file_path)
		#add source group (filter)
		self._add_source_group(file_path, index_after)
	
	def _cmake_path(self):
		return os.path.join(self._cwd, self._module_name, "CMakeLists.txt")
	
	def _read(self):
		cmake_path = self._cmake_path()
		with open(cmake_path, "r") as cmake_file:
			self._cmake_text = cmake_file.read().decode("UTF-8")
			
	def _write(self):
		cmake_path = self._cmake_path()
		with open(cmake_path, "w") as cmake_file:
			cmake_file.write(self._cmake_text.encode("UTF-8"))
			
	def _find(self, pattern):
		return find_line_by_pattern(self._cmake_text, pattern)
		
	def _insert(self, index, text, on_new_line = True):
		if on_new_line:
			text = "\n" + text
		self._cmake_text = insert_text(self._cmake_text, text, index)
		return index + len(text)
		
	def _last_appearance(self, rc):
		return last_appearance(self._cmake_text, rc)
	
	_cmake_text = ""
	_module_name = ""
	_header_path = ""
	_source_path = ""
	_cwd = ""
	
	_dry_run = False
	
	_cmake_begin_index = 0