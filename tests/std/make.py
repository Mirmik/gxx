#!/usr/bin/env	python
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application, doit
from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")

def project(parh):
	application(parh,
		sources = [parh],
		include_paths = ["../.."],
		modules = [
			submodule("gxx"),
			submodule("gxx.dprint", "stdout"),
		]
	)
	doit(parh)


project("vector.cpp")