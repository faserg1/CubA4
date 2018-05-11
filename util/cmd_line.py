#!/usr/bin/env python3

import sys

class CmdLineParser:
	def __init__(self, gen_class_func, gen_interface_func):
		self._cls_func = gen_class_func
		self._ifc_func = gen_interface_func

	def help(self):
		print("Usage:")
		print("gen.py class|interface <name> <module> [params]")
		print("")
		print("<name> -- Class or interface name with namespaces, separeted with dot (`.`).")
		print("<module> -- Module, where to place class or interface.")
	
	def parse(self):
		if len(sys.argv) < 4:
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
		print(full_name, module, params)
	
	def _parse_ifc(self, full_name, module, params):
		pass
	
	_cls_func = None
	_ifc_func = None