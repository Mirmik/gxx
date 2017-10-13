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
	target = "target",
	type = "application",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx"),
		submodule("gxx.dprint", "stdout"),
	]
)

make_module("main",
	cxxstd = "gnu++14",
)

target = "target"

licant.make.doit(target)