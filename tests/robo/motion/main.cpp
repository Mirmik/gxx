#include <gxx/print.h>
#include <gxx/robo/motion.h>

#include <thread>
#include <chrono>

int main()
{
	robo::stub_position_driver<> pdrv;
	//robo::jog_trajectory<> traj(0, 10.0 / 1000);
	robo::line_by_time_trajectory<> traj(0, -20000, 10000);
	//robo::accdcc_trajectory<> traj2(0, 5, 0, 1000, 0, 10, 10);
	traj.set_start_time(0);

	robo::axmover<> ax(&pdrv);

	ax.set_trajectory(&traj);

	int64_t millis = 0;
	while(1) {
		int sts = ax.service(millis);
		if (sts < 0) 
		{
			exit(0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		millis += 100;
	}
}