from licant.modules import module
from licant.scripter import scriptq

scriptq.execute("libc/libc.g.py")
scriptq.execute("std/std.g.py")
scriptq.execute("gxx/debug/debug.g.py")
scriptq.execute("gxx/diag/diag.g.py")

module("gxx", 
	srcdir = "gxx",
	sources = [
		"io/file_posix.cpp",
		"io/file_unix.cpp",
		"io/std.cpp",
		"inet/socket_unix.cpp",
		"inet/socket.cpp",
		"logger/targets/stdout.cpp", 
		"impl/panic_abort.cpp",
		"string.cpp",
		"util/base64.cpp",
		"util/numconvert.c"
	],

	include_paths = ["."]
)

module("gxx.include", 
	sources = [],
	include_paths = ["."]
)

module("gxx.panic", impl="abort",
	srcdir = "gxx/impl",
	sources = ["panic_abort.cpp"]
)

module("gxx.std", 
	include_paths = ["std"]
)

module("gxx.format", 
	sources = ["gxx/fmt/format.cpp"],
)

module("gxx.print", impl = "cout", 
	sources = ["gxx/print/print_cout.cpp"],
)

module("gxx.trent", 
	sources = ["gxx/serialize/json.cpp", "gxx/serialize/gbson.cpp", "gxx/serialize/trent.cpp"],
)

module("gxx.geom", 
	sources = ["gxx/geom/geom2.cpp", "gxx/geom/geom3.cpp", "gxx/geom/intersect.cpp", "gxx/geom/topo.cpp"],
)

module("gxx.cxx_support", 
	sources = ["compiler/__cxa_pure_virtual.c"],
)


module("gxx.rabbit", 
	sources = ["gxx/rabbit/crvints.cpp"],
)
