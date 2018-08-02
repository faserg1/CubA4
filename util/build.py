#!/usr/bin/env python3

import subprocess
import sys
import os
import platform

cwd = os.getcwd()
path_build = os.path.join(cwd, "build")
path_build32 = os.path.join(path_build, "x32")
path_build64 = os.path.join(path_build, "x64")
env_dir = os.path.join(cwd, "env")

def do_cmake(cmake_args, path):
	if not os.path.isdir(path):
		os.makedirs(path)
	os.chdir(path)
	result = subprocess.call(cmake_args)
	os.chdir(cwd)
	return result

def create_args(generator, path):
	return ["cmake", "-G", generator, path]
	
def check_env(cmd, filepath, env):
	total_file_path = os.path.join(env_dir, filepath)
	path = ""
	if cmd in sys.argv:
		path = sys.argv[sys.argv.index(cmd)+1].replace("\"", "")
	elif os.path.exists(total_file_path):
		with open(total_file_path, "r") as file:
			path = file.read()
	if len(path):
		os.putenv(env, path)
		with open(total_file_path, "w") as file:
			file.write(path)

def check_boost():
	check_env("--boost", "boost.txt", "BOOST_ROOT")
	
if not os.path.isdir(env_dir):
	os.makedirs(env_dir)

check_boost()

if platform.system() == "Windows":
	args32 = create_args("Visual Studio 15 2017", "../..")
	args64 = create_args("Visual Studio 15 2017 Win64", "../..")
	do_cmake(args32, path_build32)
	do_cmake(args64, path_build64)