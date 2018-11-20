#ifndef GXX_MOVER_H
#define GXX_MOVER_H

namespace robo
{
	struct axis 
	{
		robo::servo * servo;

		virtual float feedback_position() = 0;
		virtual float planed_position() = 0;
		
		virtual int move_relative(float arg) = 0;
		virtual int move_absolute(float arg) = 0;
		virtual int move_relative_trajectory(const trajectory& traj) = 0;
		virtual int move_absolute_trajectory(const trajectory& traj) = 0;

		virtual int service() = 0;
	};

	struct axgroup
	{
		std::list<robo::axis*> axes;

		int linear_interpolation(std::vector<int> idx, 
			const std::vector<robo::point> pnts);
	};
}

#endif