#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
import licant

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

application("target",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
)

licant.ex("target")