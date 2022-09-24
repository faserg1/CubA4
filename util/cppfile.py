#!/usr/bin/env python3

import sys

class CppFile:
	def __init__(self):
		self._lines = []
		self._current_line = 0
		self._indent_count = 0

	def add_lines(self, lines_open, lines_close, add_indent = True, add_lines = False):
		ar_lines_open = [line.replace("\n", "").replace("\r", "") for line in lines_open.splitlines()] if lines_open else []
		ar_lines_close = [line.replace("\n", "").replace("\r", "") for line in lines_close.splitlines()] if lines_close else []
		#open
		for line in ar_lines_open:
			self._lines.insert(self._current_line, "\t" * self._indent_count + line + "\n")
			self._current_line += 1
		if add_lines and len(ar_lines_open) > 0:
			self._lines.insert(self._current_line, "\t" * self._indent_count + "\n")
			self._current_line += 1
		#close
		for line in ar_lines_close:
			self._lines.insert(self._current_line, "\t" * self._indent_count + line + "\n")
		if add_lines and len(ar_lines_close) > 0:
			self._lines.insert(self._current_line, "\t" * self._indent_count + "\n")
		#indent
		if add_indent:
			self._indent_count += 1

	def to_string(self):
		total = ""
		for line in self._lines:
			total += line
		if sys.platform.startswith("win32"):
			total = total.replace("\n", "\r\n")
		return total

	_lines = []
	_current_line = 0
	_indent_count = 0
