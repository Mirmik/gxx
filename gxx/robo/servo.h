#ifndef GXX_ROBO_SERVO_H
#define GXX_ROBO_SERVO_H

namespace robo 
{
	struct servo 
	{
		virtual void service(float pos, float spd, float acc);
	};

	struct servo_local : public servo
	{
		float setted_power;

		float feedback_position;
		float feedback_speed;

		robo::power_writer* drv;
		robo::spdpos_reader* enc;
		
		autocontrol::xv_regulator;

		void service(float pos, float spd, float acc) override;
	};

	struct servo_remote : public servo
	{

	};
}

#endif