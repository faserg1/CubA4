#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorClass(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._file_hpp = CppFile()
		self._file_cpp = CppFile()
		self.set_virtual_destructor(False)
		self.set_empty_constructor(False)
		self.set_empty_destructor(False)
	
	def generate(self):
		self._generate_guard(self._file_hpp)
		self._generate_namespaces(self._file_hpp)
		self._generate_class_proto(self._file_hpp)
		
	def save(self):
		self._save_to_include(self._file_hpp, ".hpp")
		self._save_to_src(self._file_cpp, ".cpp")
	
	_file_hpp = None
	_file_cpp = None