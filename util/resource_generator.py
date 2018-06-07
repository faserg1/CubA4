#!/usr/bin/env python3

import os
from .resource_finder import ResourceFinder
from .resource_compiler import ResourceCompiler
from .lineutil import *

class ResourceGenerator:
	def __init__(self, module_name):
		self._cwd = os.getcwd()
		self._module_name = module_name
		self._rf = ResourceFinder(module_name)
		self._rf.find_all()
		self._gen_path = os.path.join(self._cwd, self._module_name, "gen")
		
	def generate(self):
		files = self._rf.get_files()
		if not len(files):
			return
		if not os.path.exists(self._gen_path):
			os.makedirs(self._gen_path)
		self._generate_irs_hpp()
		self._generate_irs_cpp()
		self._generate_irs_headers_hpp(files)
		self._generate_irs_data_hpp(files)
	
	def _generate_irs_hpp(self):
		pass
	
	def _generate_irs_cpp(self):
		pass
		
	def _generate_irs_headers_hpp(self, files):
		pass
		
	def _generate_irs_data_hpp(self, files):
		total = "constexpr unsigned char data[] = {\n\t"
		for file in files:
			total += "// " + file + "\n\t"
			rc = ResourceCompiler(os.path.join(self._rf.get_root(), file))
			filedata = rc.compile() + ("," if file != files[-1] else "")
			total += format_for(filedata, 70, "\n\t")
		total = total[:-1] + ";"
		filename = os.path.join(self._gen_path, "irs-data.hpp")
		with open(filename, "w") as irs_data:
			irs_data.write(total)
	
	_cwd = ""
	_module_name = ""
	_rf = None
	_gen_path = ""