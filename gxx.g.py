from glink.modules import module
from glink.scripter import scriptq

module("gxx.sources", 
	srcdir = "gxx",
	sources = [
		"format.cpp", 
		"arglist.cpp", 
		"logger/targets/stdout.cpp", 
		"print.cpp",
		"serialize/json.cpp",
		"serialize/datatree.cpp",
	]
)

scriptq.execute_recursive(root="gxx", pattern="g.py", hide="HIDE")