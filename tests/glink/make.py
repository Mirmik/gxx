#!/usr/bin/env	python3.5
#coding: utf-8

import licant
from licant.core import core
from licant.modules import module, submodule
from licant.cxx_modules import make as make_module
from licant.make import make as make
import licant.util as gu

from licant.scripter import scriptq

scriptq.execute("../../gxx.g.py")

module("main",
	sources = ["main.cpp"],
	includePaths = ["../.."],
	modules = [
		submodule("gxx.sources"),
		submodule("gxx.dprint", "stdout"),
	]
)

make_module("main",
	cxxstd = "gnu++14",
	target = "licanttest"
)

target = "licanttest"

def all():
	return licant.make.make(target)

def clean():
	return licant.make.clean(target)

def install():
	print("Делаю вид, что инсталирую")

result = gu.do_argv_routine(arg=1, default="all", locs=locals())
licant.make.print_result_string(result)
