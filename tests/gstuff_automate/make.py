#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
from licant.scripter import scriptq
import licant

scriptq.execute("../../gxx.g.py")

application("target",
	sources = ["main.c"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx.c_only"),
		submodule("gxx.dprint", "stdout"),
	],
)

licant.ex("target")
