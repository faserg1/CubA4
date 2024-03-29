#!/usr/bin/env python3

import os

class FindResult:
	def __init__(self, start, end):
		self.start = start
		self.end = end
	start = 0
	end = 0

def insert_text(source, text, index):
	return source[:index] + text + source[index:]

def find_line_by_pattern(text, compiled_re):
	match = compiled_re.search(text)
	if not match:
		return
	return FindResult(match.start(0), match.end(0))

def last_appearance(text, compiled_re_search, compiled_re_ignore = None):
	results = compiled_re_search.finditer(text)
	if not results:
		return
	last_match = None
	last_pos = 0
	for match in results:
		if compiled_re_ignore:
			to_check = match.string[last_pos:match.end(0)]
			last_pos = match.end(0)
			m_ignore = compiled_re_ignore.search(to_check)
			if not m_ignore:
				last_match = match
		else:
			last_match = match
	last_result = last_match
	if not last_result:
		return
	return FindResult(last_result.start(0), last_result.end(0))

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

def split_path(path):
	parts = []
	while True:
		path, last = os.path.split(path)
		if last != "":
			parts.append(last)
		else:
			if path != "":
				parts.append(path)
			break
	return parts[::-1]

def var_to_pattern(text):
	return text.replace("$", "\\$").replace("{", "\\{").replace("}", "\\}")

def check_exists_and_get(source, target):
	if source.startswith(target):
		after = source[len(target):]
		return after if len(after) else None

def format_for(str, every, place):
	total = ""
	parts = [str[i:i+every] for i in range(0, len(str), every)]
	for part in parts:
		total += part + place
	return total
