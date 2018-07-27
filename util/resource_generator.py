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
		if not os.path.exists(self._gen_path):
			os.makedirs(self._gen_path)
		self._generate_irs_hpp()
		self._generate_irs_cpp()
		self._generate_irs_headers_hpp(files)
		self._generate_irs_data_hpp(files)
	
	def _generate_irs_hpp(self):
		total = "#ifndef IRS_HPP\n"
		total += "#define IRS_HPP\n\n"
		total += "namespace CubA4\n{\n\tnamespace irs\n\t{\n"
		nstabs = "\t\t"
		total += nstabs + "/// \\brief Получение внутренних файлов\n"
		total += nstabs + "/// \\param[in] name Путь к файлу\n"
		total += nstabs + "/// \\param[out] size Размер файла\n"
		total += nstabs + "/// \\return Указатель на начало файла, если файл найден. Иначе nullptr.\n"
		total += nstabs + "const void *findFile(const char *name, size_t &size);\n"
		total += "\t}\n}\n\n"
		total += "#endif // IRS_HPP\n"
		filename = os.path.join(self._gen_path, "irs.hpp")
		self._write(filename, total)
	
	def _generate_irs_cpp(self):
		total = "#include \"irs.hpp\"\n"
		total += "#include \"irs-headers.hpp\"\n"
		total += "#include \"irs-data.hpp\"\n\n"
		total += "const void *CubA4::irs::findFile(const char *name, size_t &size)\n{\n"
		total += "\tconst unsigned char *ptr = data;\n"
		total += "\tsize = 0;\n"
		total += "\tauto iter = info.find(name);\n"
		total += "\tif (iter == info.end())\n"
		total += "\t\treturn nullptr;\n"
		total += "\tsize = iter->second.filesize;\n"
		total += "\tptr += iter->second.offset;\n"
		total += "\treturn ptr;\n"
		total += "}\n"
		filename = os.path.join(self._gen_path, "irs.cpp")
		self._write(filename, total)
		
	def _generate_irs_headers_hpp(self, files):
		total = "#include <map>\n"
		total += "#include <string>\n\n"
		total += "namespace\n{\n\tstruct IrsFileInfo\n\t{\n"
		total += "\t\tsize_t offset;\n"
		total += "\t\tsize_t filesize;\n"
		total += "\t};\n"
		total += "\tconst std::map<std::string, IrsFileInfo> info =\n\t{\n"
		offset = 0
		root = self._rf.get_root()
		get_size = lambda fname: os.stat(os.path.join(root, fname)).st_size
		for file in files:
			total += "\t\t{"
			total += "\"" + file.replace("\\", "/") + "\", "
			size = get_size(file)
			total += "{" + str(offset) + ", " + str(size) + "}"
			total += "},\n"
			offset += size
		total += "\t};\n}\n"
		filename = os.path.join(self._gen_path, "irs-headers.hpp")
		self._write(filename, total)
		
	def _generate_irs_data_hpp(self, files):
		total = "constexpr unsigned char data[] = {\n\t"
		for file in files:
			total += "//\n\t"
			total += "// " + file + "\n\t"
			total += "//\n\t"
			rc = ResourceCompiler(os.path.join(self._rf.get_root(), file))
			filedata = rc.compile() + ("," if file != files[-1] else "")
			total += format_for(filedata, 70, "\n\t")
		total = total[:-1] + "};"
		filename = os.path.join(self._gen_path, "irs-data.hpp")
		self._write(filename, total)
			
	def _write(self, filename, data):
		with open(filename, "wb") as file:
			file.write(data.encode("UTF-8"))
	
	_cwd = ""
	_module_name = ""
	_rf = None
	_gen_path = ""