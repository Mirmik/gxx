#ifndef GXX_LOG_MANAGER_H
#define GXX_LOG_MANAGER_H

//#include <gxx/time/datetime.h>
#include <gxx/log/base.h>
//#include <gxx/log/logger.h>
#include <memory>
#include <vector>

namespace gxx {
	namespace log {

		class logger;
		class target;
		class logmessage;

		class manager {
		public:
			/*std::condition_variable cvar;
			std::mutex cvar_mtx;
			std::mutex cvar_mtx;
			std::mutex datamtx;
			std::vector<logger*> loggers;
			std::queue<std::shared_ptr<logmessage>> msgqueue;

			void log(std::shared_ptr<logmessage> sptr, bool syncmode) {
				if (syncmode) logimpl(sptr);
				else {
					datamtx.lock();
					msgqueue.push_back(sptr);
					datamtx.unlock();
					cvar.notify_one();
				}
			}

			void async_thread_function() {
				while (1) {
					datamtx.lock();
					if (msgqueue.empty()) {
						datamtx.unlock();
						std::unique_lock
						cvar_mtx.
					}
			
					std::shared_ptr<logmessage> sptr = 
				
				}
			}*/

		//	dlist<logger, &logger::manage_link> loggers;
		//	dlist<target, &target::manage_link> targets;
			
		//	manager(){
		//		dprln("Construct LogManager.");
		//	}
//
		//	void registry(logger& l) {
		//		loggers.move_back(l);
		//	}
//
		//	void registry(target& t) {
		//		targets.move_back(t);
		//	}
		//};
	
		//manager& LogManager();
		};
	}
}

#endif