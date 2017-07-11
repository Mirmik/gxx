script:evalFile("../../gxx.gll", _ENV)

ruller = CXXDeclarativeRuller.new{
		buildutils = { 
		CXX = "g++", 
		CC = "gcc", 
		LD = "ld",  
	},
	--weakRecompile = "noscript",
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
		{name = "gxx.log_manager"},
		{name = "gxx.dprint", impl = "stdout"},
	},

	includeModules = {
		{name = "gxx.include"}
	},
	
	sources = {
		cxx = "main.cpp"
	},
})

local ret = ruller:standartAssemble("main", {
	target = "target",
	targetdir = "./",
	assembletype = "application"
})

if not ret then print(text.yellow("Nothing to do")) end