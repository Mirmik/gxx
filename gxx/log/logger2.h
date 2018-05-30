#ifndef GXX_LOGGER_H
#define GXX_LOGGER_H

#include <gxx/datastruct/dlist_head.h>

#include <gxx/time/datetime.h>
#include <gxx/log/manager.h>
#include <gxx/log/base.h>
#include <gxx/print.h>
#include <vector>
#include <memory>

namespace gxx {
	namespace log {
		class target;

		class logger {
			dlist_head manage_link;
			std::string logger_name;
			std::vector<std::pair<gxx::log::target*, gxx::log::level>> targets;
			bool syncmode = false;
		
		public:
			logger(const std::string& name) : logger_name(name) {}

			void link(target& tgt, level lvl) { targets.push_back(std::make_pair(&tgt,lvl)); }
			void clear_targets() { targets.clear(); }

			inline void log(level lvl, std::string&& msg) {
				auto logmsg = std::allocate_shared<logmessage>(gxx::log::alloc);
				logmsg->time = gxx::time::now();
				logmsg->message = std::move(msg);
				logmsg->level = lvl;
				logmsg->logger = this;

				manager.log(logmsg, syncmode);
			}

			template <typename ... Args>
			inline void log(level lvl, const char* fmt, Args&& ... args) {
				log(lvl, gxx::format(fmt, args ...));
			}

			template <typename ... Args>
			inline void log(level lvl, std::string& fmt, Args&& ... args) {
				log(lvl, fmt.c_str(), gxx::make_visitable_arglist<gxx::fmt::format_visitor>(std::forward<Args>(args) ...));
			}

			template <typename ... Args>
			inline void trace(Args&& ... args) {
				log(level::trace, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void debug(Args&& ... args) {
				log(level::debug, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void info(Args&& ... args) {
				log(level::info, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void warn(Args&& ... args) {
				log(level::warn, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void error(Args&& ... args) {
				log(level::error, std::forward<Args>(args)...);
			}

			template <typename ... Args>
			inline void fault(Args&& ... args) {
				log(level::fault, std::forward<Args>(args)...);
			}
		};		
	}
}

#endif
