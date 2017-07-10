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
		enum class Level {
			Trace,
			Debug,
			Info,
			Warning,
			Error, 
			Fault, 
		};
		
		//Вызов для формирования строки даты/времени.

		class logger {
			const char* logger_name = "Logger";
			std::vector<gxx::log::target*> targets;
			std::string pattern = "[{level}]{logger}: {msg}";

			Level minlevel = Level::Trace;

		public:
			dlist_head manage_link;
			
			void(*timestamp)(char* time, size_t maxlen) = nullptr;
			
			SETTER(set_timestamp_callback, timestamp);
			CONSTREF_GETTER(timestamp_callback, timestamp);

			logger(const char* name) : logger_name(name) {}

			void link(target& tgt) {
				targets.push_back(&tgt);
			}

			void set_pattern(const char* str) {
				pattern = str;
			}

			void set_level(Level level) {
				minlevel = level;
			}


			/*template <typename ... Args>
			inline void log_helper(Level level, const char* fmt, argument<Args>&& ... args) {
				log()
			}*/

			inline void log(Level level, const char* fmt, arglist&& args) {
				if (minlevel <= level) {
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
						"level"_a=level_to_str(level),
						"time"_a=tstamp
					);

					logmsg.append("\n");
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
			inline void log(Level level, const char* fmt, Args&& ... args) {
				log(level, fmt, gxx::arglist(gxx::make_argument<format_visitor>(gxx::make_argument_temporary(std::forward<Args>(args))) ...));
			}

			template <typename ... Args>
			inline void trace(const char* fmt, Args&& ... args) {
				log(Level::Trace, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void debug(const char* fmt, Args&& ... args) {
				log(Level::Debug, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void info(const char* fmt, Args&& ... args) {
				log(Level::Info, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void warn(const char* fmt, Args&& ... args) {
				log(Level::Warning, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void error(const char* fmt, Args&& ... args) {
				log(Level::Error, fmt, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void fault(const char* fmt, Args&& ... args) {
				log(Level::Fault, fmt, std::forward<Args>(args)...);
			}

			static const char* level_to_str(Level level) {
				switch(level) {
					case Level::Trace: return "trace";
					case Level::Debug: return "debug";
					case Level::Info: return "info";
					case Level::Warning: return "warn";
					case Level::Error: return "error";
					case Level::Fault: return "fault";
				}
			}

		};
	}
}

#endif