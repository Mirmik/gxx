#ifndef GXX_ROBO_MOTION_H
#define GXX_ROBO_MOTION_H

#include <gxx/print.h>

#include <gxx/robo/trajectory.h>

namespace robo
{
	template <typename P=int64_t, typename V=float, typename A=float>
	struct position_driver
	{
		virtual void service(P d0, V d1, A d2) = 0;
		virtual P position() = 0;
	};

	template <typename P=int64_t, typename V=float, typename A=float>
	struct stub_position_driver : public position_driver<P,V,A>
	{
		P curpos;

		void service(P d0, V d1, A d2) override
		{
			curpos = d0;
			gxx::fprintln("({},{},{})", d0, d1, d2);
		}

		P position() override 
		{
			return curpos;
		}
	};

	template <typename P=int64_t, typename V=float, typename A=float, typename T=time_t>
	struct axmover 
	{
		robo::position_driver<P,V,A>*	_drv;
		robo::trajectory<P,V,A,T>*		_traj;

		axmover(robo::position_driver<P,V,A>* drv) : _drv(drv), _traj(nullptr) {}

		int service(T time) 
		{
			robo::phase<P,V,A> phs;
			int sts;

			if (_traj) 
			{
				sts = _traj->inabstime(time, &phs);
				if (sts != 0)
					return sts;

				_drv->service(phs.d0, phs.d1, phs.d2);
			}
		} 

		P position() const
		{
			return _drv->position();
		}

		void set_trajectory(robo::trajectory<P,V,A,T>* traj) 
		{
			_traj = traj;
		}
	};
}

#endif