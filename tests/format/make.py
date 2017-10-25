#!/usr/bin/env	python3.5
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application, doit

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

application("main",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx.include"),
		submodule("gxx.dprint", "stdout"),
		submodule("gxx.panic", "abort"),
		submodule("gxx.print"),
	]
)

doit("main")