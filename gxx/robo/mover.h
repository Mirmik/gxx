#ifndef GXX_MOVER_H
#define GXX_MOVER_H

namespace robo
{
	template <typename type = double>
	struct phase
	{
		type d0;
		type d1;
		type d2;
	}

	template <typename TimeDiff, typename Coord>
	struct law
	{
		virtual phase<Coord> in_moment(TimeDiff t);
	}

	template <typename TimeDiff, typename Coord>
	struct simple_law : public law
	{
		time_interval interval;
		Coord start;
		Coord finish;

		phase<Coord> in_moment(TimeDiff t) override
		{
			return phase<Coord> { 
				start + interval.koeff(t) * (finish-start), 
				(finish-start) / interval.length()};
		}
	}

	template <typename type = double>
	struct time_interval
	{
		type start;
		type interval;
	}

	phase<type> simple_law(type moment)
	{
		return phase<type> (  );
	}

	template <typename type = double>
	struct move_task
	{
		time_interval interval;

		phase<> (*law) (const time_interval& interval, type moment);

		//virtual phase<> current_phase();
	}

	struct axis
	{
		void enable_dispatcher();
		void disable_dispatcher();
	}

	struct group
	{
		//struct axis * axes;
		//int dim;

		virtual int move_relative(uint8_t* idxs, int lvec, double* dists);
	}
}

#endif