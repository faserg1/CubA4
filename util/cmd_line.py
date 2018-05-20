#!/usr/bin/env python3

import sys

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
		print("--ctr:empty — Set empty realization in header to constructor.")
		print("--dtr:empty — Set empty realization in header to desctructor.")
		print("--header-folder:<folder> — Set empty realization in header to desctructor.")
		print("--source-folder:<folder> — Set empty realization in header to desctructor.")
	
	def parse(self):
		if len(sys.argv) == 2:
			arg = sys.argv[1]
			if arg == "--help":
				self.help()
			elif arg == "--author":
				print("Ookami")
			return
		if len(sys.argv) < 4:
			print("Invalid usage!")
			self.help()
			return
		type = sys.argv[1]
		full_name = self._parse_name(sys.argv[2])
		module = sys.argv[3]
		params = sys.argv[4:]
		if type == "class":
			self._parse_cls(full_name, module, params)
		elif type == "interface":
			self._parse_ifc(full_name, module, params)
		
	def _parse_name(self, name):
		return name.split(".")
		
	def _parse_cls(self, full_name, module, params):
		self._cls_func(full_name, module, params)
	
	def _parse_ifc(self, full_name, module, params):
		self._ifc_func(full_name, module, params)
	
	_cls_func = None
	_ifc_func = None