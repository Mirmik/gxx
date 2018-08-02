#!/usr/bin/env	python3.5
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

import licant

application("target",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.trent"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
)

licant.ex("target")