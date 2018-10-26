#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
import licant

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")


bu = licant.cxx_make.binutils(
	cxx="clang++",
	cc="clang",
	ld="clang",
	ar="ar",
	objdump="objdump"
)

application("target",
	sources = ["main.c"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
)

licant.fileset("all", ["target"])

licant.ex("all")