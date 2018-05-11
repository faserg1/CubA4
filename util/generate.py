#!/usr/bin/env python3

import re
import sys
import os
import copy

from .cmd_line import CmdLineParser
from .generator_class import GeneratorClass
from .generator_interface import GeneratorInterface

def generate_class(full_name, module, params):
	generator = GeneratorClass(full_name, module)
	
def generate_interface(full_name, module, params):
	generator = GeneratorInterface(full_name, module)

parser = CmdLineParser(generate_class, generate_interface)
parser.parse()