from licant.modules import module
from licant.scripter import scriptq

scriptq.execute("libc/libc.g.py")
scriptq.execute("std/std.g.py")
scriptq.execute("gxx/debug/debug.g.py")
scriptq.execute("gxx/diag/diag.g.py")

module("gxx", 
	srcdir = "gxx",
	sources = [
#		"format.cpp", 
		#"arglist.cpp", 
		"io/fstream_posix.cpp",
		"io/fstream_unix.cpp",
		"inet/socket_unix.cpp",
		"inet/socket.cpp",
		"fmt/format.cpp",
		"logger/targets/stdout.cpp", 
		#"print.cpp",
		"serialize/json.cpp",
		"serialize/trent.cpp",
		"impl/panic_abort.cpp"
	],

	include_paths = ["."]
)

module("gxx.include", 
	include_paths = ["."]
)

module("gxx.panic", impl="abort",
	srcdir = "gxx/impl",
	sources = ["panic_abort.cpp"]
)

module("gxx.std", 
	include_paths = ["std"]
)
	
