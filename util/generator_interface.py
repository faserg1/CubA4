#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorInterface(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._file_hpp = CppFile()
		self.set_virtual_destructor(True)
		self.set_default_constructor(True)
		self.set_default_destructor(True)
		if self._ctr_access == "public":
			self.set_access_constructor("protected")
		
	def generate(self):
		self._generate_guard(self._file_hpp)
		self._generate_namespaces(self._file_hpp)
		self._generate_class_proto(self._file_hpp)
		
	def save(self):
		self._save_header(self._file_hpp)
		
	_file_hpp = None