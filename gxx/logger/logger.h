#ifndef GXX_LOGGER_H
#define GXX_LOGGER_H

#include <gxx/logger/target.h>
#include <gxx/format.h>
#include <gxx/vector.h>
#include <gxx/string.h>
#include <gxx/shared.h>

using namespace gxx::literals;

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

		class logger {
			vector<target*> targets;
			gxx::string pattern = "*** {logger}::{msg} ***";

		public:
			void link(target& tgt) {
				targets.push_back(&tgt);
			}

			void set_pattern(const char* str) {
				pattern = str;
			}

			/*template <typename ... Args>
			inline void log_helper(Level level, const char* fmt, argument<Args>&& ... args) {
				log()
			}*/

			inline void log(Level level, const char* fmt, arglist<format_generic>&& args) {
				char msg[128];
				memory_writer writer(msg, 128);
				format_impl(writer, fmt, args);

				gxx::string logmsg = format(pattern.c_str(), "msg"_a=msg);
				

				/*for (auto t : targets) {
					t->log(logmsg.c_str());
				}*/
			}

			template <typename ... Args>
			inline void log(Level level, const char* fmt, Args&& ... args) {
				log(level, fmt, arglist<format_generic>(argument<Args>(args)...));
			}

			template <typename ... Args>
			inline void trace(const char* fmt, Args&& ... args) {
				log(Level::Trace, fmt, gxx::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void debug(const char* fmt, Args&& ... args) {
				log(Level::Debug, fmt, gxx::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void info(const char* fmt, Args&& ... args) {
				log(Level::Info, fmt, gxx::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void warn(const char* fmt, Args&& ... args) {
				log(Level::Warning, fmt, gxx::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void error(const char* fmt, Args&& ... args) {
				log(Level::Error, fmt, gxx::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void fault(const char* fmt, Args&& ... args) {
				log(Level::Fault, fmt, gxx::forward<Args>(args)...);
			}

		};
	}
}

#endif