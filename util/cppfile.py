#!/usr/bin/env python3

class CppFile:
	def add_lines(self, lines_open, lines_close, add_indent = True, add_lines = False):
		ar_lines_open = [line.replace("\n", "").replace("\r", "") for line in lines_open.splitlines()]
		ar_lines_close = [line.replace("\n", "").replace("\r", "") for line in lines_close.splitlines()]
		
		for line in ar_lines_open:
			self._lines.insert(self._current_line, "\t" * self._indent_count + line + "\n")
			self._current_line += 1
		if add_lines:
			self._lines.insert(self._current_line, "\t" * self._indent_count + "\n")
			self._current_line += 1
		for line in ar_lines_close:
			self._lines.insert(self._current_line, "\t" * self._indent_count + line + "\n")
		if add_lines:
			self._lines.insert(self._current_line, "\t" * self._indent_count + "\n")
		if add_indent:
			self._indent_count += 1
			
	def to_string(self):
		total = ""
		for line in self._lines:
			total += line
		return total
	
	_lines = []
	_current_line = 0
	_indent_count = 0