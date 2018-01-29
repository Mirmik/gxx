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
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.trent"),

		submodule("gxx.rabbit"),
	],
	ld_flags = "-lX11"
)

doit("main")