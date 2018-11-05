#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
import licant

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")


bu = licant.cxx_make.binutils(
	cxx="clang++",
	cc="clang",
	ld="clang",
	ar="ar",
	objdump="objdump"
)

application("target",
	sources = ["main.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
#	binutils = bu,

	#cxx_flags = "-Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector",
	cxx_flags="-g",
	cc_flags="-std=gnu11 -g"
)

licant.ex("target")