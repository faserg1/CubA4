#!/usr/bin/env python3

import sys
import os

class CmdLineParser:
	def __init__(self, gen_class_func, gen_interface_func):
		self._cls_func = gen_class_func
		self._ifc_func = gen_interface_func

	def help(self):
		print("Usage:")
		print("gen.py class|interface <name> <module> [params]")
		print("Where:")
		print("<name> — Class or interface name with namespaces, separeted with dot (`.`).")
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
	
	def parse(self):
		if len(sys.argv) == 2:
			arg = sys.argv[1]
			if arg == "--help":
				self.help()
			elif arg == "--author":
				print("Ookami")
			self.help()
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
		full_name = self._parse_name(sys.argv[2])
		module = sys.argv[3]
		params = sys.argv[4:]
		if not self._check(type, full_name, module):
			return
		if type == "class":
			self._parse_cls(full_name, module, params)
		elif type == "interface":
			self._parse_ifc(full_name, module, params)
	
	def _check(self, type, full_name, module):
		if type != "class" and type != "interface":
			print("Invalid type <" + type + ">!")
			return False
		path_module = os.path.join(os.getcwd(), module)
		if not os.path.exists(path_module) or not os.path.isdir(path_module):
			print("Module <" + module + "> not found.")
			return False
		return True
		
	
	def _parse_name(self, name):
		return name.split(".")
		
	def _parse_cls(self, full_name, module, params):
		self._cls_func(full_name, module, params)
	
	def _parse_ifc(self, full_name, module, params):
		self._ifc_func(full_name, module, params)
	
	_cls_func = None
	_ifc_func = None