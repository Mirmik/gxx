#!/usr/bin/env	python
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
import licant

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

application("target",
	sources = ["main.c"],
	include_paths = ["../.."],
	include_modules = [
		("gxx", "posix"),
		("gxx.dprint", "stdout")
	]
)

licant.ex(default="target")