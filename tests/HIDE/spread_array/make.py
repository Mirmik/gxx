#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
from licant.scripter import scriptq
import licant

scriptq.execute("../../gxx.g.py")

application("target",
	sources = ["main.c", 
	#"test1.c", 
	#"test2.c"
	],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "stdout"),
		submodule("gxx.print", "cout"),
	],
#	cxx_flags = "-pedantic -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align 
#-Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow 
#-Woverloaded-virtual",

	cc_flags = "-std=gnu11",
	ld_flags = "-T ../../gxx/datastruct/array_spread.lds.S"
)

licant.ex(default = "target")

#licant.ex("target")
