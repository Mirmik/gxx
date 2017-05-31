#ifndef GXX_LOGGER_MANAGER_H
#define GXX_LOGGER_MANAGER_H

#include <gxx/dlist.h>
#include <gxx/debug/dprint.h>
#include <gxx/logger/logger.h>
#include <gxx/logger/target.h>

namespace gxx {
	namespace log {
		class manager {
		public:
			dlist<logger, &logger::manage_link> loggers;
			dlist<target, &target::manage_link> targets;
			
			manager(){
				dprln("Construct LogManager.");
			}

			void registry(logger& l) {
				loggers.move_back(l);
			}

			void registry(target& t) {
				targets.move_back(t);
			}
		};
	
		//manager& LogManager();
	}
}

#endif