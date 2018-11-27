#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
from licant.scripter import scriptq
import licant

scriptq.execute("../../../gxx.g.py")

application("target",
	sources = ["main.cpp"],
	include_modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "stdout"),
		submodule("gxx.print", "cout"),
	],

	cxx_flags = "-Werror=all -pedantic-errors -Werror=return-type"
)

licant.ex(default = "target")