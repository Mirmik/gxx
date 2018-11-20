#ifndef GXX_TRACE_H
#define GXX_TRACE_H

//#include <gxx/log/logger2.h>
#include <gxx/print.h>
#include <gxx/arglist.h>

using namespace gxx::argument_literal;

//gxx::log::logger* trace_log = nullptr;
extern uint8_t trace_level;

namespace gxx {
//inline void set_trace_logger(gxx::log::logger* logger) {
//    trace_log = logger;
//}

struct tracer {
    const char* func = func;

    tracer(const char* func) {
        this->func = func;
        //gxx::fprintln(fmt, trace_level, func);
        dpr("TRACE: "); dpr(trace_level); dpr(": -> "); dprln(func);
        ++trace_level;
    }

    ~tracer() {
        --trace_level;
        dpr("TRACE: "); dpr(trace_level); dpr(": <- "); dprln(func);
    }
};
}

#define TRACE() gxx::tracer __tracer(__PRETTY_FUNCTION__)

#endif
