#!/usr/bin/env python3

import sys
import os

class CmdLineParser:
	def __init__(self, gen_class_func, gen_interface_func, gen_struct_func):
		self._type_map = {"class": gen_class_func, "interface": gen_interface_func, "struct": gen_struct_func}

	def help(self):
		print("Usage:")
		print("gen.py class|interface|struct <name> <module> [params]")
		print("Where:")
		print("<name> — Class or interface name with namespaces, separeted with dot (`.`).\nIf name starts with '#', namespace will be ignored, but folder created.")
		print("<module> — Module, where to place class or interface.")
		print("Parameters:")
		print("--dry-run — Not add files at really, but do work.")
		print("--ctr:<access_mod> — Set access modifier to constructor.")
		print("--dtr:<access_mod> — Set access modifier to desctructor.")
		print("--dtr:virtual — Desctructor will be virtual.")
		print("--ctr:default — Set default realization in header to constructor.")
		print("--dtr:default — Set default realization in header to desctructor.")
		print("--header-folder:<folder> — Set folder for .hpp files.")
		print("--source-folder:<folder> — Set folder for .cpp files.")
		print("--module-namespace — Will not ignore module namespace")
		print("--json — Will add json to struct")

	def parse(self):
		if len(sys.argv) == 2:
			arg = sys.argv[1]
			if arg == "--help":
				self.help()
			elif arg == "--author":
				print("Ookami")
			#self.help()
			return
		if len(sys.argv) < 4:
			print("Invalid usage!")
			self.help()
			return
		req_params = sys.argv[1:4]
		for req_param in req_params:
			if req_param.startswith("--"):
				print("Invalid usage!")
				self.help()
				return
		type = sys.argv[1]
		full_name = sys.argv[2]
		module = sys.argv[3]
		params = sys.argv[4:]
		if not self._check(type, full_name, module):
			return
		parse_func = self._type_map[type]
		parse_func(full_name, module, params)

	def _check(self, type, full_name, module):
		if type not in self._type_map:
			print("Invalid type <" + type + ">!")
			return False
		path_module = os.path.join(os.getcwd(), module)
		if not os.path.exists(path_module) or not os.path.isdir(path_module):
			print("Module <" + module + "> not found.")
			return False
		return True

	_type_map = {}