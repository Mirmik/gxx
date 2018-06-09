from licant.modules import module
from licant.scripter import scriptq

scriptq.execute("libc/libc.g.py")
scriptq.execute("std/std.g.py")
scriptq.execute("gxx/debug/debug.g.py")
scriptq.execute("gxx/diag/diag.g.py")

module("gxx", "posix",
	srcdir = "gxx",
	sources = [
		"io/file_unix.cpp",
		"io/std.cpp",
		"impl/panic_abort.cpp",
		"util/string.cpp",
		"util/base64.cpp",
		"util/hexascii.cpp",
		"util/numconvert.c",
		"osutil/src/posix.cpp",
		"path/path.cpp",
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

module("gxx.parser", 
	sources = ["gxx/parser/json_lex.cpp"],
)

module("gxx.log", impl = "posix", 
	sources = ["gxx/log/posix_timestamp.cpp", "gxx/log/targets/stdout.cpp"],
)

module("gxx.log2", 
	sources = ["gxx/log/src/logger.cpp", "gxx/log/src/synconly.cpp"],
)

module("gxx.trent", 
	srcdir = "gxx/trent",
	sources = ["json.cpp", "gbson.cpp", "trent.cpp"],
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

module("gxx.util", 
	srcdir = "gxx",
	sources = [
		#"util/string.cpp",
		#"util/base64.cpp",
		"util/numconvert.c"
	],
)

module("gxx.inet", "posix",
	srcdir = "gxx/inet/src",
	sources = [ "common.cpp", "posix.cpp" ],		
)

module("gxx.inet", "windows",
	srcdir = "gxx/inet/src",
	sources = [ "common.cpp", "windows.cpp" ],		
)