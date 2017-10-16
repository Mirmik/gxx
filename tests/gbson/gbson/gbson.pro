QT -= core
CONFIG += c++14 warn_off console
CONFIG -= qt

HEADERS = ../../../gxx/**.h

INCLUDEPATH += ../../../

OBJECTS_DIR = build
TARGET = target

SOURCES = main.cpp
SOURCES += ../../../gxx/debug/dprintxx.cpp
SOURCES += ../../../gxx/debug/dprint_stdout.c
SOURCES += ../../../gxx/debug/dprint_func_impl.c
SOURCES += ../../../gxx/logger/targets/stdout.cpp
SOURCES += ../../../gxx/fmt/format.cpp
SOURCES += ../../../gxx/serialize/trent.cpp
SOURCES += ../../../gxx/serialize/gbson.cpp
SOURCES += ../../../gxx/serialize/json.cpp
SOURCES += ../../../gxx/impl/panic_abort.cpp
