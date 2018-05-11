#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorInterface(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._file_hpp = CppFile()
		
	def generate(self):
		self._generate_guard(self._file_hpp)
		self._generate_namespaces(self._file_hpp)
		
	def save(self):
		self._save_to_include(self._file_hpp, ".hpp")
		
	_file_hpp = None