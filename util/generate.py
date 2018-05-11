#!/usr/bin/env python3

import re
import sys
import os
import copy

from .cppfile import CppFile
from .lineutil import *
		
def generate_guard(file, name):
	upper_file_name = name.upper() + "_HPP"
	header_guard_starts = "#ifndef " + upper_file_name + "\n"
	header_guard_define = "#define " + upper_file_name + "\n"
	header_guard_ends = "#endif // " + upper_file_name + "\n"
	file.add_lines(header_guard_starts + header_guard_define, header_guard_ends, False, True)

def generate_namespaces(file, namespaces):
	for namespace in namespaces:
		namespace_open = "namespace " + namespace + "\n{"
		namespace_close = "}"
		file.add_lines(namespace_open, namespace_close)

f = CppFile()
generate_guard(f, "NiceAndWelcome")
generate_namespaces(f, ["CubA4", "core"])
print(f.to_string())
	
def generate_namespaces(file, namespaces):
	pass

#def generate_class(name, project_folder, namespaces):
#	header_file_name = name + ".hpp"
#	source_file_name = name + ".cpp"
#
#	folders_mapped_to_namespaces_temp = copy.deepcopy(namespaces)
#	if folders_mapped_to_namespaces_temp[0] == "CubA4":
#		folders_mapped_to_namespaces_temp = folders_mapped_to_namespaces_temp[1:]
#	folders_mapped_to_namespaces = [folder.lower() for folder in folders_mapped_to_namespaces_temp]
#	
#	header_file_path = os.path.join(project_folder, "include", *folders_mapped_to_namespaces, header_file_name)
#	source_file_path = os.path.join(project_folder, "src", *folders_mapped_to_namespaces, source_file_name)
#	
#	upper_file_name = name.upper() + "_HPP"
#	header_guard_starts = "#ifndef " + upper_file_name + "\n"
#	header_guard_define = "#define " + upper_file_name + "\n\n"
#	header_guard_ends = "\n#endif" + "// " + upper_file_name + "\n"
#	
#	header_namespace_begins = "namespace CubA4\n{\n\tnamespace core\n\t{\n"
#	header_namespace_ends = "\t}\n}\n"
#	
#	header_class_define = "\t\tclass " + name + "\n\t\t{\n"
#	header_class_public = "\t\tpublic:\n"
#	header_class_ctr = "\t\t\texplicit " + name + "();\n"
#	header_class_dtr = "\t\t\t~" + name + "();\n"
#	header_class_ends = "\t\t};\n"
#	
#	with open(header_file_path, "w") as header_file:
#		header_outs = [header_guard_starts, header_guard_define,
#			header_namespace_begins,
#			header_class_define, header_class_public,
#			header_class_ctr, header_class_dtr,
#			header_class_ends,
#			header_namespace_ends, header_guard_ends]
#		for header_out in header_outs:
#			header_file.write(header_out)
#			
#	source_include_start = "#include \"../include/" + header_file_name + "\"\n"
#	source_using_namespace = "using namespace CubA4::core;\n\n"
#	
#	source_ctr_realization = name + "::" + name + "()\n{\n\t\n}\n\n"
#	source_dtr_realization = name + "::~" + name + "()\n{\n\t\n}\n\n"
#			
#	with open(source_file_path, "w") as source_file:
#		source_outs = [source_include_start, source_using_namespace,
#			source_ctr_realization, source_dtr_realization]
#		for source_out in source_outs:
#			source_file.write(source_out)