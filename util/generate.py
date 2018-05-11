#!/usr/bin/env python3

import re
import sys
import os
import copy

from .cmd_line import CmdLineParser
from .generator_class import GeneratorClass
from .generator_interface import GeneratorInterface

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

def generate_class(full_name, module, params):
	generator = GeneratorClass(full_name, module)
	generate_common(generator, params)
	if "--dtr:virtual" in params:
		generator.set_virtual_destructor(True)
	if "--ctr:empty" in params:
		generator.set_empty_constructor(True)
	if "--dtr:empty" in params:
		generator.set_empty_destructor(True)
	generator.generate()
	generator.save()
	
def generate_interface(full_name, module, params):
	generator = GeneratorInterface(full_name, module)
	generate_common(generator, params)
	generator.generate()
	generator.save()

parser = CmdLineParser(generate_class, generate_interface)
parser.parse()