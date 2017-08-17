print("HelloWorld")

from glink.modules import module

module("gxx.sources", 
	sources = [
		"format.cpp", 
		"arglist.cpp", 
		"logger/targets/stdout.cpp", 
		"print.cpp",
		"serialize/json.cpp",
		"serialize/datatree.cpp",
	]
)