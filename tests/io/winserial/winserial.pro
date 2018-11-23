TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt


LIBS += -lws2_32 -liconv

SOURCES += main.cpp

SOURCES += ../../../gxx/io/file_windows.cpp


INCLUDEPATH += ../../../


SOURCES += ../../../gxx/debug/dprintxx.cpp
SOURCES += ../../../gxx/debug/dprint_stdout.c
SOURCES += ../../../gxx/debug/dprint_func_impl.c
SOURCES += ../../../gxx/log/targets/stdout.cpp
SOURCES += ../../../gxx/log/posix_timestamp.cpp
SOURCES += ../../../gxx/impl/panic_abort.c
SOURCES += ../../../gxx/impl/sshell.c
SOURCES += ../../../gxx/src/printf_impl.c
SOURCES += ../../../gxx/trent/trent.cpp
SOURCES += ../../../gxx/trent/json.cpp
SOURCES += ../../../gxx/path/path.cpp
SOURCES += ../../../gxx/util/string.cpp
SOURCES += ../../../gxx/impl/trace.cpp

SOURCES += ../../../gxx/print/src/impl/print_cout.cpp
SOURCES += ../../../gxx/util/numconvert.c

SOURCES += ../../../gxx/util/base64.cpp
SOURCES += ../../../gxx/io/std.cpp
