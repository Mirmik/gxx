from licant.modules import module, submodule
from licant.scripter import scriptq

scriptq.execute("libc/libc.g.py")
scriptq.execute("std/std.g.py")
scriptq.execute("posix/posix.g.py")
scriptq.execute("gxx/debug/debug.g.py")
scriptq.execute("gxx/diag/diag.g.py")

module("gxx.util.c",
	srcdir = "gxx",
	sources = [
		"util/numconvert.c",
		"util/hexer.c",
		"gstuff/gstuff.c",
		"gstuff/autorecv.c",
		"impl/trace.cpp",
		"util/dstring.c",
		"impl/sshell.c",
		"impl/panic_abort.c",
		"src/printf_impl.c",
		"math/util.c",
		"debug/delay.c",
	],
)

module("gxx.util.cxx",
	srcdir = "gxx",
	sources = [
		"util/string.cpp",
		"util/base64.cpp",
		"util/hexascii.cpp",
	],
)

module("gxx.include",
	include_paths = ["."]
)

module("gxx", "posix",
	srcdir = "gxx",
	sources = [
		"datastruct/src/tree.c",
		"io/file_unix.cpp",
		"io/std.cpp",
		"io/src/ostream.cpp",
		"osutil/src/posix.cpp",
		"path/path.cpp",
	],

	include_modules = [ submodule("gxx.include"), submodule("gxx.util.c"), submodule("gxx.util.cxx") ],
)

module("gxx", "windows",
	srcdir = "gxx",
	sources = [
		"datastruct/src/tree.c",
		"io/file_windows.cpp",
		"io/std.cpp",
		"io/src/ostream.cpp",
		"osutil/src/osutil_windows.cpp",
		"path/path.cpp",
	],

	include_modules = [ submodule("gxx.include"), submodule("gxx.util.c"), submodule("gxx.util.cxx") ],
)

module("gxx.c_only",
	srcdir = "gxx",
	sources = [
		"datastruct/src/tree.c",
	],
	include_modules = [ submodule("gxx.include"), submodule("gxx.util.c")],
)

#module("gxx", "windows",
#	srcdir = "gxx",
#	sources = [
#		"io/file_windows.cpp",
#		"io/std.cpp",
#		"impl/panic_abort.cpp",
		#"osutil/src/windows.cpp",
#		"path/path.cpp",
#		"util/string.cpp",
#		"util/base64.cpp",
#		"util/hexascii.cpp",
#		"util/numconvert.c",
#		"util/hexer.c",
#	],

	#include_modules = ["gxx.util_sources"],
#	include_paths = ["."]
#)


#module("gxx.util",
#	srcdir = "gxx",
#	sources = [
#		"util/string.cpp",
#		"util/base64.cpp",
#		"util/hexascii.cpp",
#		"util/numconvert.c",
#		"util/hexer.c",
#	],
#
#	include_paths = ["."]
#)
#
#module("gxx.atomic_section", impl="mutex",
#	srcdir = "gxx/impl",
#	sources = ["atomic_section_mutex.cpp"]
#)

module("gxx.syslock", impl="mutex",
	srcdir = "gxx/impl",
	sources = ["syslock_mutex.cpp"]
)

module("gxx.syslock", impl="genos.atomic",
	srcdir = "gxx/impl",
	sources = ["syslock_genos_atomic.cpp"]
)

module("gxx.panic", impl="abort",
	srcdir = "gxx/impl",
	sources = ["panic_abort.c"]
)

module("gxx.serial", "posix",
	srcdir = "gxx",
	sources = ["serial/src/impl/unix.cpp", "serial/src/serial.cpp"]
)

module("gxx.serial", "windows",
	srcdir = "gxx",
	sources = ["serial/src/impl/win.cpp", "serial/src/serial.cpp"]
)

#module("gxx.format",
#	sources = ["gxx/fmt/format.cpp"],
#)
#
module("gxx.print", impl = "cout",
	sources = ["gxx/print/src/impl/print_cout.cpp"],
)

module("gxx.print", impl = "dprint",
	sources = ["gxx/print/src/impl/print_debug.cpp"],
)

#module("gxx.parser",
#	sources = ["gxx/parser/json_lex.cpp"],
#)

module("gxx.log", impl = "posix",
	sources = ["gxx/log/posix_timestamp.cpp", "gxx/log/targets/stdout.cpp"],
)

#module("gxx.log2", "stub",
#	sources = ["gxx/log/src/logger_stub.cpp"],
#)
#
#module("gxx.log2", "impl",
#	sources = ["gxx/log/src/logger.cpp", "gxx/log/src/synconly.cpp"],
#)

module("gxx.trent",
	srcdir = "gxx/trent",
	sources = ["json.cpp", "gbson.cpp", "trent.cpp"],
)

#module("gxx.geom",
#	sources = ["gxx/geom/geom2.cpp", "gxx/geom/geom3.cpp", "gxx/geom/intersect.cpp", "gxx/geom/topo.cpp"],
#)

#module("gxx.cxx_support",
#	sources = ["compiler/__cxa_pure_virtual.c"],
#)

module("gxx.rabbit",
	sources = ["gxx/rabbit/crvints.cpp"],
)

module("gxx.inet", "posix",
	srcdir = "gxx/inet/src",
	sources = [ "common.cpp", "posix.cpp" ],
)


module("gxx.madgwick",
	srcdir = "gxx/math",
	sources = [ "madgwick.cpp" ],
)

#module("gxx.inet", "windows",
#	srcdir = "gxx/inet/src",
#	sources = [ "common.cpp", "windows.cpp" ],
#)
