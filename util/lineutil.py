#!/usr/bin/env python3

def insert_text(source, text, index):
	return source[:index] + text + source[index:]

def find_line_by_pattern(full_file, compiled_re):
	match = compiled_re.search(full_file)
	if not match:
		return -1
	return match.end(0)
	
def camel_case(input_str, first_drop = False):
	output_str = ""
	need_upper = not first_drop
	for symbol in input_str:
		if symbol == "_":
			need_upper = True
			continue
		if need_upper:
			symbol = symbol.upper()
			need_upper = False
		output_str += symbol
	return output_str