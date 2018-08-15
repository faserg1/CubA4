#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorClass(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._file_hpp = CppFile()
		self._file_cpp = CppFile()
		self.set_virtual_destructor(False)
		self.set_default_constructor(False)
		self.set_default_destructor(False)
	
	def generate(self):
		#Header
		self._generate_guard(self._file_hpp)
		self._generate_namespaces(self._file_hpp)
		self._generate_class_proto(self._file_hpp)
		#Source
		self._generate_cpp(self._file_cpp)
		
	def save(self):
		self._save_header(self._file_hpp)
		self._save_source(self._file_cpp)
	
	_file_hpp = None
	_file_cpp = None