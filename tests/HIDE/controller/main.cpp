#include <gxx/controlling.h> 
#include <gxx/print.h>

class Axis : public gxx::controlled {
public:
	void stop() {
		if (controller_ptr()) controller_ptr()->finalize();
	}
};

class InterpolationGroup : public gxx::controller {
public:
	void init_work(Axis& ax1, Axis& ax2) {
		ax1.link_controller(this);
		ax2.link_controller(this);
		set_finalize_handler(gxx::make_delegate(&InterpolationGroup::finalize, this));
		set_work_state();
	}

	void finalize() {
		gxx::println(statestr());
		gxx::println("HelloWorld");
	} 
};

int main() {
	Axis ax1;
	Axis ax2;
	InterpolationGroup igroup;
	
	igroup.init_work(ax1, ax2);
	ax1.stop();

	gxx::println(igroup.statestr());
}