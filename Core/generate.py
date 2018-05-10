#!/usr/bin/env python3

import re
import sys
import os

GEN_FOLDER = os.path.dirname(os.path.realpath(__file__))

def insert_text(source, text, index):
	return source[:index] + text + source[index:]

def insert_line(file_path, str, pos):
	full_file = ""
	with open(file_path, "r") as file:
		full_file = file.read()
	full_file = insert_text(full_file, str, pos)
	
	with open(file_path, "w") as file:
		file.write(full_file)

def find_line_by_pattern(file_path, compiled_re):
	full_file = ""
	with open(file_path, "r") as file:
		full_file = file.read()
	match = compiled_re.search(full_file)
	return match.end(0)
		
def generate_class(name):
	header_file_name = name + ".hpp"
	source_file_name = name + ".cpp"

	header_file_path = os.path.join(GEN_FOLDER, "include", header_file_name)
	source_file_path = os.path.join(GEN_FOLDER, "src", source_file_name)
	
	upper_file_name = name.upper() + "_HPP"
	header_guard_starts = "#ifndef " + upper_file_name + "\n"
	header_guard_define = "#define " + upper_file_name + "\n\n"
	header_guard_ends = "\n#endif" + "// " + upper_file_name + "\n"
	
	header_namespace_begins = "namespace CubA4\n{\n\tnamespace core\n\t{\n"
	header_namespace_ends = "\t}\n}\n"
	
	header_class_define = "\t\tclass " + name + "\n\t\t{\n"
	header_class_public = "\t\tpublic:\n"
	header_class_ctr = "\t\t\texplicit " + name + "();\n"
	header_class_dtr = "\t\t\t~" + name + "();\n"
	header_class_ends = "\t\t};\n"
	
	with open(header_file_path, "w") as header_file:
		header_outs = [header_guard_starts, header_guard_define,
			header_namespace_begins,
			header_class_define, header_class_public,
			header_class_ctr, header_class_dtr,
			header_class_ends,
			header_namespace_ends, header_guard_ends]
		for header_out in header_outs:
			header_file.write(header_out)
			
	source_include_start = "#include \"../include/" + header_file_name + "\"\n"
	source_using_namespace = "using namespace CubA4::core;\n\n"
	
	source_ctr_realization = name + "::" + name + "()\n{\n\t\n}\n\n"
	source_dtr_realization = name + "::~" + name + "()\n{\n\t\n}\n\n"
			
	with open(source_file_path, "w") as source_file:
		source_outs = [source_include_start, source_using_namespace,
			source_ctr_realization, source_dtr_realization]
		for source_out in source_outs:
			source_file.write(source_out)
	
def add_class_to_list(name):
	header_file_name = name + ".hpp"
	source_file_name = name + ".cpp"

	list_file_name = os.path.join(GEN_FOLDER, "CMakeLists.txt")
	header_defines_re = re.compile("(set\\w*\\(\\w*CoreHeaders)")
	source_defines_re = re.compile("(set\\w*\\(\\w*CoreSources)")
	
	to_write_header = "\n\t${CoreIncludeDir}/"  + header_file_name
	to_write_source = "\n\t${CoreSourceDir}/"  + source_file_name
	
	write_headers = find_line_by_pattern(list_file_name, header_defines_re)		
	insert_line(list_file_name, to_write_header, write_headers)
	
	write_sources = find_line_by_pattern(list_file_name, source_defines_re)	
	insert_line(list_file_name, to_write_source, write_sources)

def print_help():
	print("To generate class, type `generate class <class name>`")

def switcher():
	if len(sys.argv) < 2:
		print_help()
		return
	cmd = sys.argv[1]
	if cmd == "help":
		print_help()
	elif cmd == "class":
		if len(sys.argv) < 3:
			print_help()
			return
		class_name = sys.argv[2]
		generate_class(class_name)
		add_class_to_list(class_name)
	
if __name__ == "__main__":
	switcher()