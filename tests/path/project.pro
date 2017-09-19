CONFIG += c++14

SOURCES += main.cpp

SOURCES += ../../gxx/path/path_windows.cpp
SOURCES += ../../gxx/io/fstream_windows.cpp
SOURCES += ../../gxx/io/printable.cpp
SOURCES += ../../gxx/io/ostream.cpp
SOURCES += ../../gxx/string.cpp


SOURCES += ../../gxx/debug/dprint_func_impl.c
SOURCES += ../../gxx/debug/dprint_stdout.c
SOURCES += ../../gxx/debug/dprintxx.cpp

INCLUDEPATH = ../..
