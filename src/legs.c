#include "legs.h"

struct Leg Legs[6];
uint8_t LegsUpdated = 0;

void updateServo(uint32_t pulse_us, struct ServoConf *conf)
{
	if ((pulse_us < 700) || (pulse_us > 2300)) return;
	switch (conf->OC)
	{
		case 1:
		{
			TIM_SetCompare1(conf->TIM, pulse_us);
			break;
		}
		case 2:
		{
			TIM_SetCompare2(conf->TIM, pulse_us);
			break;
		}
		case 3:
		{
			TIM_SetCompare3(conf->TIM, pulse_us);
			break;
		}
		case 4:
		{
			TIM_SetCompare4(conf->TIM, pulse_us);
			break;
		}
	}
}

void updateLegs()
{
	for (int i = 0; i < 6; i++)
	{
		updateServo(Legs[i].H1, &Legs[i].H1Conf);
		updateServo(Legs[i].V2, &Legs[i].V2Conf);
		updateServo(Legs[i].V3, &Legs[i].V3Conf);
	}
	LegsUpdated = 1;
}
