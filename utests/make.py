#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

include("gxx")

tests = [
	"print/print",
	"print/log",
#	"event",
#	"access",
	"convert/hexascii",
	"convert/base64",
	"geom/interval",
	"container/pool",
	"math/float",

	"debug/dprint",
]

application("runtests",
	sources = ["main.cpp"] + [t+".cpp" for t in tests],

	ld_flags = "-L/usr/local/lib/",

	include_paths = ["."],
	include_modules = [
		submodule("gxx", "posix"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.log", "posix"),
	],

	libs = ["gtest", "pthread"]
)

licant.ex("runtests")