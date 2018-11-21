#ifndef GXX_ROBO_PLANNING_H
#define GXX_ROBO_PLANNING_H

namespace robo
{
	template <typename type = double>
	struct phase
	{
		type d0;
		type d1;
		type d2;
	};

	template <typename TimeDiff, typename Coord>
	struct trajectory
	{
		dlist_head lnk; // Для подключения в стэк траекторий.
		virtual phase<Coord> in_moment(TimeDiff t);
	};

	template <typename TimeDiff, typename Coord>
	struct group_trajectory
	{
		dlist_head lnk; // Для подключения в стэк траекторий.
		virtual phase<Coord> in_moment(TimeDiff t, int axnum);
	};




	template <typename TimeDiff, typename Coord>
	struct simple_trajectory : public trajectory
	{
		TimeDiff interval;

		Coord start;
		Coord finish;

		phase<Coord> in_moment(TimeDiff t) override
		{
			if (t > interval)
				return phase<Coord> { finish, 0, 0 }

			else
				return phase<Coord> {
					start + (t / interval) * (finish - start),
					(finish - start) / interval,
					0
				};
		}
	};

	template <typename TimeDiff, typename Coord>
	struct parabolic_trajectory 
	{
		double x0;
		double v0;
	
		double a;
		double aDiv2;
		double interval;

		phase<Coord> in_moment(TimeDiff t, phase<Coord>& ret) override
		{
			vinc = a * t;
			xinc = vinc * t / 2;

			ret.d0 = x0 + xinc;
			ret.d1 = v0 + vinc;
			ret.d2 = a;

			return t < interval;
		}
	}

	template <typename TimeDiff, typename Coord>
	struct line_trajectory 
	{
		double x0;
		
		double v;
		double interval;

		phase<Coord> in_moment(TimeDiff t, phase<Coord>& ret) override
		{
			ret.d0 = x0 + v * t;
			ret.d1 = v;
			ret.d2 = 0;

			return t < interval;
		}
	}

	template <typename TimeDiff, typename Coord>
	struct acc_dcc_trajectory 
	{
		double x0;
		double x1;

		parabolic_trajectory 	acctraj;
		parabolic_trajectory 	dcctraj;
		line_trajectory 		lintraj;

		double linstart;
		double dccstart;

		double interval;

		phase<Coord> in_moment(TimeDiff t, phase<Coord>& ret) override
		{
			if (t >= interval) {
				ret.d0 = x1;
				ret.d1 = 0;
				ret.d2 = 0;
	
				return false;
			} 

			if (t >= dccstart) {
				dcctraj(t, ret);
				return true;
			}

			if (t >= linstart) {
				lintraj(t, ret);
				return true;
			}		

			acctraj(t, ret);
			return true;	
		}

		acc_dcc_trajectory(double x0, double x1, double acc, double dcc, double spd);
		static acc_dcc_trajectory by_time(double x0, double x1, double acc, double dcc, double time);
	}
}

#endif