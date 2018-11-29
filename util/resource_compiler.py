#!/usr/bin/env python3

import os
import tempfile

class ResourceCompiler:
	def __init__(self, path):
		self._path = path
		self._tempfile = tempfile.TemporaryFile(mode="w+")

	def compile(self):
		f = open(self._path, "rb")
		try:
			byte = f.read(1)
			while byte:
				self._tempfile.write("0x" + byte.hex())
				byte = f.read(1)
				if byte:
					self._tempfile.write(",")
		finally:
			f.close()
		self._tempfile.seek(0, 0)
		return self._tempfile.read()

	_path = ""
	_tempfile = None
