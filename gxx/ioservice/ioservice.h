#ifndef GXX_IO_SERVICE_H
#define GXX_IO_SERVICE_H

#include <gxx/container/dlist.h>

namespace gxx {
	namespace tasks {

		class schedule;

		class task {
			dlist_head lnk;
			
			bool have_done = false;
			bool need_unbind = false;
			task* cont;

			virtual void doit(task_service* srvs) = 0;
			
			//void unplan() { dlist_del(&lnk); }
			operator bool() { return have_done; }
		};
	
		class schedule {
			dlist<task, &task::lnk> planed_task;
		};

	}
}


void local_test() {

	gxx::tasks::schedule sch;

	gxx::tasks::fd_loop_read reader(sch, 2, true);
	gxx::tasks::fd_loop_read reader(sch, 2, true);




}



#endif