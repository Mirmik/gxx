#ifndef GXX_ROBO_SERVO_H
#define GXX_ROBO_SERVO_H

namespace robo 
{
	struct servo 
	{
		virtual void update() = 0;		
	};

	struct servo_local : public servo
	{
		float setted_power;

		float feedback_position;
		float feedback_speed;
		float feedback_acceleration;

		robo::power_writer* drv;
		robo::spdpos_reader* enc;
		
		autocontrol::xv_regulator;

		void update() override;
	};

	struct servo_remote : public servo
	{

	};
}

#endif