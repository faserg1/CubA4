#!/usr/bin/env python3

import re
import sys
import os
import copy

from .cmd_line import CmdLineParser
from .generator_class import GeneratorClass
from .generator_interface import GeneratorInterface
from .generator_struct import GeneratorStruct
#from .cmake_patcher import CMakePatcher
from .lineutil import *

def generate_common(generator, params):
	if "--dry-run" in params:
		generator.set_dry_run(True)
	if "--ctr:public" in params:
		generator.set_access_constructor("public")
	if "--ctr:protected" in params:
		generator.set_access_constructor("protected")
	if "--ctr:private" in params:
		generator.set_access_constructor("private")
	if "--dtr:public" in params:
		generator.set_access_destructor("public")
	if "--dtr:protected" in params:
		generator.set_access_destructor("protected")
	if "--dtr:private" in params:
		generator.set_access_destructor("private")
	if "--module-namespace" in params:
		generator.set_module_namespace(True)
	if "--json" in params:
		generator.set_need_json(True)
	for param in params:
		header_folder = check_exists_and_get(param, "--header-folder:")
		if header_folder:
			generator.set_header_folder(header_folder)
		source_folder = check_exists_and_get(param, "--source-folder:")
		if source_folder:
			generator.set_source_folder(source_folder)

def patcher_options(patcher, params):
	if "--dry-run" in params:
		patcher.set_dry_run(True)

def generate_class(full_name, module, params):
	generator = GeneratorClass(full_name, module)
	generate_common(generator, params)
	if "--dtr:virtual" in params:
		generator.set_virtual_destructor(True)
	if "--ctr:default" in params:
		generator.set_default_constructor(True)
	if "--dtr:default" in params:
		generator.set_default_destructor(True)
	generator.generate()
	generator.save()
	#patcher = CMakePatcher(module, generator.header_saved_to(), generator.source_saved_to())
	#patcher_options(patcher, params)
	#patcher.patch()

def generate_interface(full_name, module, params):
	generator = GeneratorInterface(full_name, module)
	generate_common(generator, params)
	generator.generate()
	generator.save()
	#patcher = CMakePatcher(module, generator.header_saved_to(), generator.source_saved_to())
	#patcher_options(patcher, params)
	#patcher.patch()

def generate_struct(full_name, module, params):
	generator = GeneratorStruct(full_name, module)
	generate_common(generator, params)
	generator.generate()
	generator.save()

parser = CmdLineParser(generate_class, generate_interface, generate_struct)
parser.parse()
