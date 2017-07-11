script:evalFile("../../gxx.gll", _ENV)

ruller = CXXDeclarativeRuller.new{
		buildutils = { 
		CXX = "g++", 
		CC = "gcc", 
		LD = "ld",  
	},
	--weakRecompile = "noscript",
	optimization = "-O3",
	standart = {
		cxx = "-std=c++1z",
		cc = "-std=gnu11",
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