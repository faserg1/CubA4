#!/usr/bin/env python3

import os

class CMakePatcher:
	def __init__(self, project_name):
		self._cwd = os.getcwd()
		self._project_name = project_name
		self._parse()
	
	def _parse(self):
		pass
	
	_project_name = ""
	_cwd = ""