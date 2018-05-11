#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorInterface(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._file_hpp = CppFile()
		
	_file_hpp = None