from glink.modules import module
from glink.scripter import scriptq

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
		"fmt/format.cpp",
		"logger/targets/stdout.cpp", 
		#"print.cpp",
		#"serialize/json.cpp",
		#"serialize/datatree.cpp",
	],

	include_paths = ["."]
)
