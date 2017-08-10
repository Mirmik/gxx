#ifndef GXX_LOGGER_H
#define GXX_LOGGER_H

#include <gxx/datastruct/dlist_head.h>
#include <gxx/logger/target.h>
#include <gxx/format.h>

#include <vector>
#include <string>
#include <memory>

#include <gxx/util/setget.h>

using namespace gxx::argument_literal;
//using namespace std::string_literal;

namespace gxx {
	namespace log {
		enum class level {
			trace,
			debug,
			info,
			warn,
			error, 
			fault, 
		};

		static level level_from_string(std::string str) {
			if (str == "fault") return level::fault;
			if (str == "error") return level::error;
			if (str == "warn") return level::warn;
			if (str == "info") return level::info;
			if (str == "debug") return level::debug;
			return level::trace;
		}	

		static const char* level_to_string(level lvl) {
			switch(lvl) {
				case level::trace: return "trace";
				case level::debug: return "debug";
				case level::info : return "info";
				case level::warn : return "warn";
				case level::error: return "error";
				case level::fault: return "fault";
			}
		}

		class logger {
			const char* logger_name = "Logger";
			std::vector<gxx::log::target*> targets;
			std::string pattern = "[{level}]{logger}: {msg}";

			level minlevel = level::trace;

		public:
			dlist_head manage_link;
			
			void(*timestamp)(char* time, size_t maxlen) = nullptr;
			
			SETTER(set_timestamp_callback, timestamp);
			CONSTREF_GETTER(timestamp_callback, timestamp);

			logger(const char* name) : logger_name(name) {}

			void link(target& tgt) {
				targets.push_back(&tgt);
			}

			void clear_targets() {
				targets.clear();
			}

			void set_pattern(const char* str) {
				pattern = str;
			}

			void set_level(level lvl) {
				minlevel = lvl;
			}


			/*template <typename ... Args>
			inline void log_helper(level_type level, const char* fmt, argument<Args>&& ... args) {
				log()
			}*/

			inline void log(level lvl, const char* fmt, arglist&& args) {
				if (minlevel <= lvl) {
					std::string msg = gxx::format_args(fmt, args);

					char tstamp[64] = "";
					if (timestamp != nullptr) timestamp(tstamp, 64);
	
					//int loglen = strlen(pattern.c_str()) * 2 + msglen + 50;
					//char* logmsg = (char*)alloca(loglen);
					//memory_stream logstrm(logmsg, loglen);
					//text_writer logwriter(logstrm);
					std::string logmsg = format(
						pattern.c_str(), 
						"msg"_a=msg.c_str(), 
						"logger"_a=logger_name,
						"level"_a=log::level_to_string(lvl),
						"time"_a=tstamp
					);

					//logmsg.append("\n");
/*
					std::string logmsg = format(pattern.c_str(), 
						"msg"_a=(const char*)msg, 
						"logger"_a=logger_name,
						"level"_a=level_to_str(level),
						"time"_a=tstamp);
*/					
					//dprln(logmsg);
				
					for (auto t : targets) {
						t->log(logmsg.c_str());
					}
				}
			}

			template <typename ... Args>
			inline void log(level lvl, const char* fmt, Args&& ... args) {
				log(lvl, fmt, gxx::arglist(gxx::make_argument<format_visitor>(gxx::make_argument_temporary(std::forward<Args>(args))) ...));
			}

			template <typename ... Args>
			inline void trace(const char* fmt, Args&& ... args) {
				log(level::trace, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void debug(const char* fmt, Args&& ... args) {
				log(level::debug, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void info(const char* fmt, Args&& ... args) {
				log(level::info, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void warn(const char* fmt, Args&& ... args) {
				log(level::warn, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void error(const char* fmt, Args&& ... args) {
				log(level::error, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void fault(const char* fmt, Args&& ... args) {
				log(level::fault, fmt, std::forward<Args>(args)...);
			}
		};		
	}
}

#endif