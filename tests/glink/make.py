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
	sources = ["main.cpp"],
	includePaths = ["../.."],
	modules = [submodule("gxx.sources")]
)

make_module("main",
	cxxstd = "gnu++14",
)


#make("build/arglist.cpp")
make("target")

exit(0)

target = "target"

def all():
	return glink.make.make(target)

def clean():
	return glink.make.clean(target)

def install():
	print("Делаю вид, что инсталирую")

result = gu.do_argv_routine(arg=1, default="all", locs=locals())
glink.make.print_result_string(result)
