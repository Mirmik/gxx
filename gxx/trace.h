#ifndef GXX_TRACE_H
#define GXX_TRACE_H

//#include <gxx/log/logger2.h>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>
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
    std::string ret;

    tracer(const char* func) {
        this->func = func;
        //gxx::fprintln(fmt, trace_level, func);
        dpr("TRACE: "); dpr(trace_level); dpr(": -> "); dpr(func);
        ++trace_level;
    }

    ~tracer() {
        --trace_level;
        dpr("TRACE: "); dpr(trace_level); dpr(": <- "); dpr(func);
        if (ret != "") 
        {
            dpr(":"); gxx::println(ret); 
        } 
        else 
        {
            dprln();
        }
    }
};
}

#if defined(NOTRACE) && NOTRACE!=0
#define TRACE()
#define TRRET(ex) ex
#define TRACE_ARGS(...)
#else
#define TRACE() gxx::tracer __tracer(__PRETTY_FUNCTION__); dln();
#define TRRET(ex) ({ auto __ret = (ex); __tracer.ret = std::to_string(__ret); return __ret; __ret; })
#define TRACE_ARGS(...) gxx::tracer __tracer(__PRETTY_FUNCTION__); dpr(" with "); gxx::println(__VA_ARGS__);
#endif

#endif
