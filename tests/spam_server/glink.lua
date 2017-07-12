script:evalFile("../../gxx.gll", _ENV)

ruller = CXXDeclarativeRuller.new{
		buildutils = { 
		CXX = "g++", 
		CC = "gcc", 
		LD = "ld",  
	},
	weakRecompile = "noscript",
	optimization = "-O2",
	standart = {
		cxx = "-std=c++14",
		cc = "-std=c11",
	},
	flags = {
		cc = "",
		cxx = "",
		ld = "",
		allcc = "-Wl,--gc-sections -fdata-sections -ffunction-sections"
	},
	builddir = "./build",
}

Module("main", {
	modules = {
		{name = "gxx.sources"},
		--{name = "gxx.io", impl = "unix"},
		{name = "gxx.dprint", impl = "stdout"},
		{name = "gxx.socket", impl = "unix"},
	},

	includeModules = {
		{name = "gxx.include"}
	},
	
	sources = {
		cxx = "main.cpp"
	},

	libs = "boost_system"
})

local ret = ruller:standartAssemble("main", {
	target = "target",
	targetdir = "./",
	assembletype = "application"
})

if not ret then print(text.yellow("Nothing to do")) end