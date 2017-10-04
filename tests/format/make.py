#!/usr/bin/env	python3.5
#coding: utf-8

from glink.modules import submodule
from glink.cxx_modules import application, doit

from glink.scripter import scriptq
scriptq.execute("../../gxx.g.py")

application("main",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx"),
		submodule("gxx.dprint", "stdout"),
	]
)

doit("main")