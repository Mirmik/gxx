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
		submodule("gxx", "posix"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.trent"),
	],
	ld_flags = "-lX11"
)

doit("main")