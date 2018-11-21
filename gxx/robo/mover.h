#ifndef GXX_AXIS_MOVER_H
#define GXX_AXIS_MOVER_H

namespace robo
{
	struct axmover 
	{
		robo::servo * servo;
		robo::trajectory * traj;

		float feedback_position();
		float feedback_speed();

		float planed_position();
		float planed_speed();
		
		//int move_relative(float arg);
		//int move_absolute(float arg);
		
		int move_relative_trajectory(robo::trajectory * traj);
		int move_absolute_trajectory(robo::trajectory * traj);

		int service();
	};

	struct axgroup
	{
		std::list<robo::axis*> axes;



		int linear_interpolation(std::vector<int> idx, 
			const std::vector<robo::point> pnts);

		int move_group_trajectory(robo::group_trajectory gtraj);
	};

	struct axmulti 
	{
		int dim;
		robo::servo ** servos;

		time_t startop;
		group_trajectory<time_t, float> * gtraj;

		void update() 
		{
			for (int i; i< dim; ++i) 
			{
				auto phase = gtraj.in_moment(millis() - startop);
				servos[i]->service(phase.d0, phase.d1, phase.d2);
			}
		}
	}
}

#endif