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

def generate_class(full_name, module, params):
	generator = GeneratorClass(full_name, module)
	generate_common(generator, params)
	generator.generate()
	generator.save()
	
def generate_interface(full_name, module, params):
	generator = GeneratorInterface(full_name, module)
	generate_common(generator, params)
	generator.generate()
	generator.save()

parser = CmdLineParser(generate_class, generate_interface)
parser.parse()