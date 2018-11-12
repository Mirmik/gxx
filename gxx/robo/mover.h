#ifndef GXX_MOVER_H
#define GXX_MOVER_H

namespace robo
{
	struct servo_local
	{
		float x;
		float v;

		robo::power_writer* drv;
		robo::spdpos_reader* enc;
		
		autocontrol::xv_regulator;

		void update();
	}

	struct servo_remote 
	{

	}

	struct group
	{
	


	}
}

#endif