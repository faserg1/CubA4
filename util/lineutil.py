#!/usr/bin/env python3

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