#!/usr/bin/env python3

from licant.cxx_modules import application, doit
from licant.modules import submodule, module
from licant.libs import include

include("gxx")

tests = [
	"print",
	"event",
]

application("runtests",
	sources = ["main.cpp"] + [t+".cpp" for t in tests],

	include_paths = ["."],
	include_modules = [
		submodule("gxx"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
	],

	libs = ["gtest", "gmock", "pthread"]
)

doit("runtests")