#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

include("gxx")

tests = [
	"print/print",
#	"event",
#	"access",
	"convert/hexascii",
	"convert/base64",
	"geom/interval",
	"container/pool",
]

application("runtests",
	sources = ["main.cpp"] + [t+".cpp" for t in tests],

	include_paths = ["."],
	include_modules = [
		submodule("gxx", "posix"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
	],

	libs = ["gtest", "gmock", "pthread"]
)

licant.ex("runtests")