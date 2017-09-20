#!/usr/bin/env	python3.5
#coding: utf-8

import glink
from glink.core import core
from glink.modules import module, submodule
from glink.cxx_modules import make as make_module
from glink.make import make as make
import glink.util as gu

from glink.scripter import scriptq

scriptq.execute("../../gxx.g.py")

module("main",
	target = "target",
	type = "application",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx"),
		submodule("gxx.dprint", "stdout"),
		#submodule("gxx.io", "posix"),
	]
)

make_module("main",
	cxxstd = "gnu++14",
)

target = "target"

glink.make.doit(target)