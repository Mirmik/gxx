from licant import *

module("gxx.dprint.common", "impl", 
	sources=["dprint_func_impl.c", "dprintxx.cpp"],
	mdepends=["gxx.printf"]
)

implementation("gxx.dprint", "stub", 
	sources = "dprint_func_stub.c dprint_stub.c dprintxx.cpp".split(" ")
)

implementation("gxx.dprint", "diag", 
	sources = ["dprint_diag.c"],
	cc_flags = "-Wno-pointer-to-int-cast",
	mdepends = [
		"gxx.diag",
		("gxx.dprint.common", "impl")
	],
)

implementation("gxx.dprint", "manually", 
	sources = ["dprint_manually.c"],
	mdepends = [("gxx.dprint.common","impl")],
)

implementation("gxx.dprint", "stdout",
	sources = ["dprint_stdout.c"],
	mdepends = [("gxx.dprint.common","impl")],
)

module_defimpl("gxx.dprint", "stdout")