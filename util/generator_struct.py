#!/usr/bin/env python3

from .generator_base import GeneratorBase
from .cppfile import CppFile

class GeneratorStruct(GeneratorBase):
	def __init__(self, full_name, module_name):
		super().__init__(full_name, module_name)
		self._need_json = False
		self._file_hpp = CppFile()
		self._file_cpp = CppFile()
		self.set_container_name("struct")
		self.set_virtual_destructor(False)
		self.set_default_constructor(False)
		self.set_default_destructor(False)
		self.set_has_ctr(False)
		self.set_has_dtr(False)

	def set_need_json(self, value):
		self._need_json = value

	def generate(self):
		#Header
		self._generate_guard(self._file_hpp)
		if self._need_json:
			self._file_hpp.add_lines("#include <nlohmann/json_fwd.hpp>\n", None, False, True)
		self._generate_namespaces(self._file_hpp)
		if self._need_json:
			self._generate_json_header(self._file_hpp)
		self._generate_class_proto(self._file_hpp)
		#Source
		includes = []
		if self._need_json:
			includes.append("<nlohmann/json.hpp>")
		self._generate_cpp(self._file_cpp, includes)
		if self._need_json:
			self._generate_json_source(self._file_cpp)


	def _generate_json_header(self, file_header: CppFile):
		name = self._get_name()
		j_name = "nlohmann::json"
		h_define = "void to_json({1}& j, const {0}& v);\nvoid from_json(const {1}& j, {0}& v);\n".format(name, j_name)
		file_header.add_lines(None, h_define, False, True)
		

	def _generate_json_source(self, file_source: CppFile):
		name = self._get_name()
		j_name = "nlohmann::json"
		namespaces = "::".join(self._get_namespaces())
		c_declare1 = "void {2}::to_json({1}& j, const {0}& v)\n{{\n\t\n}}\n\n".format(name, j_name, namespaces)
		c_declare2 = "void {2}::from_json(const {1}& j, {0}& v)\n{{\n\t\n}}\n\n".format(name, j_name, namespaces)
		c_declare = c_declare1 + c_declare2
		file_source.add_lines(c_declare, None, False, True)

	def save(self):
		self._save_header(self._file_hpp)
		if self._need_json:
			self._save_source(self._file_cpp)

	_file_hpp = None
	_file_cpp = None
	_need_json = False
