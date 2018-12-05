#ifndef GXX_ROBO_TRAJECTORY_H
#define GXX_ROBO_TRAJECTORY_H

#include <gxx/datastruct/dlist.h>

namespace robo
{
	template <typename P = int64_t, typename V = float, typename A = float>
	struct phase
	{
		P d0;
		V d1;
		A d2;
	};

	template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct trajectory
	{
		void set_start_time(T time)
		{
			_start = time;
		}

		int inabstime(T time, phase<P, V, A>* phs)
		{
			return inloctime(time - _start, phs);
		}

		virtual int inloctime(T time, phase<P, V, A>* phs) = 0;

	public:
		dlist_head lnk; // Для подключения в стэк траекторий.

	private:
		T _start;
	};

	template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct keep_trajectory : public trajectory<P, V, A, T> 
	{
		P x;

		keep_trajectory(P pos) : x(pos) {};

		int inloctime(T t, phase<P, V, A>* phs) override
		{
			phs->d0 = x;
			phs->d1 = 0;
			phs->d2 = 0;

			return 0;
		}
	};


	template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct jog_trajectory : public trajectory<P, V, A, T>
	{
		P x0;
		V v;

		jog_trajectory(P spos, V speed) : x0(spos), v(speed) {};

		int inloctime(T t, phase<P, V, A>* phs) override
		{
			phs->d0 = x0 + v * t;
			phs->d1 = v;
			phs->d2 = 0;

			return 0;
		}
	};

	template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct line_by_time_trajectory : public trajectory<P, V, A, T>
	{
		P x0;
		P x1;
		T t01;

		P x01;
		V v;

		line_by_time_trajectory(P spos, P fpos, T interval) : x0(spos), x1(fpos), t01(interval)
		{
			x01 = x1 - x0;
			v = (V)x01 / (V)t01;
		}

		int inloctime(T t, phase<P, V, A>* phs) override
		{
			if (t > t01)
				return -1;

			phs->d0 = x0 + ((float)t / (float)t01) * x01;
			phs->d1 = v;
			phs->d2 = 0;

			return 0;
		}
	};

	/*template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct acceleration_trajpart : public trajectory<P, V, A, T>
	{
		P x0;
		V v0;
		A a;

		acceleration_trajpart (P spos, V sspd, A acc)
			: x0(spos), v0(sspd), a(acc)
		{}

		int inloctime(T t, phase<P, V, A>* phs) override
		{
			V vinc = a * t;
			P xinc = (vinc * t) / 2;

			phs->d0 = x0 + xinc;
			phs->d1 = v0 + vinc;
			phs->d2 = a;

			return 0;
		}
	};*/

	template <typename P = int64_t, typename V = float, typename A = float, typename T = time_t>
	struct accdcc_trajectory : public trajectory<P, V, A, T>
	{
		P x0;
		P x1;
		P x01;

		V v;
		V v0;
		V v1;

		A a;
		A d;

		T at;
		T dt;

		accdcc_trajectory(P _x0, P _x1, V _v0, V _v, V _v1, T _at, T _dt) 
			: x0(_x0), x1(_x1), x01(_x1-_x0), v0(_v0), v(_v), v1(_v1), at(_at), dt(_dt)
		{
			assert(at >= 0);
			assert(dt >= 0);
			assert(v - v0 > 0);
			assert(v - v1 > 0);

			a = (v - v0) / (float)at;
			d = (v - v1) / (float)dt;

			P integral_a = at * (v0 + (v - v0) / 2);
			P integral_b = dt * (v1 + (v - v1) / 2);
			P integral = integral_a + integral_b;

			if (integral > x01) 
			{
				gxx::println("triangle mode");

				float koeff = x01 / integral
				float tkoeff = at / dt;
			}

			GXX_PRINT(at);
			GXX_PRINT(dt);
			GXX_PRINT(a);
			GXX_PRINT(d);
			GXX_PRINT(integral_a);
			GXX_PRINT(integral_b);
			GXX_PRINT(integral);

			exit(0);
		}

		int inloctime(T t, phase<P, V, A>* phs) override
		{
	


		}
	};
}

#endif