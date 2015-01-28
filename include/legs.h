#ifndef __LEGS_H
#define __LEGS_H

#define LEG_R1 0
#define LEG_R2 1
#define LEG_R3 2
#define LEG_L1 5
#define LEG_L2 4
#define LEG_L3 3

#include <stdint.h>
#include "stm32f4xx_tim.h"

struct ServoConf
{
	int OC;
	TIM_TypeDef *TIM;
	int Reversed;
};

struct Leg
{
	uint32_t H1, V2, V3;
	struct ServoConf H1Conf, V2Conf, V3Conf;
};

extern struct Leg Legs[6];

extern void updateLegs();
extern void updateServo(uint32_t pulse_us, struct ServoConf *conf);

extern uint8_t LegsUpdated;

#endif
