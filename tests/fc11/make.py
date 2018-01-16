#!/usr/bin/env	python
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application, doit

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

application("main",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx"),
		
		submodule("gxx.dprint", "stdout"),
		submodule("gxx.print", "cout"),
	],
	cxxstd = "gnu++11",
)

doit("main")