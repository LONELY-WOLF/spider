#include "walk_math.h"
#include <math.h>

uint32_t RadToPulse(float angle)
{
	return (uint32_t) (1500.0 + (angle * (2000.0 / M_PI)));
}

void SetLegPos(int legNum, float lx, float ly, float lz)
{
	float h = sqrtf((lx * lx) + (ly * ly));
	float d = h - LENGTH_L1;
	float l0 = sqrtf((d * d) + (lz * lz));
	float alpha0 = asinf(lz / l0);
	float alpha1 = asinf(lx / h);
	float alpha2 = acosf(((l0 * l0) + (LENGTH_L2 * LENGTH_L2) - (LENGTH_L3 * LENGTH_L3)) / (2 * l0 * LENGTH_L2));
	alpha2 -= alpha0;
	float alpha3 = acosf(((LENGTH_L2 * LENGTH_L2) + (LENGTH_L3 * LENGTH_L3) - (l0 * l0)) / (2 * LENGTH_L2 * LENGTH_L3));
	alpha3 -= M_PI_2;

	if(Legs[legNum].H1Conf.Reversed)
	{
		Legs[legNum].H1 = RadToPulse(-alpha1);
	}
	else
	{
		Legs[legNum].H1 = RadToPulse(alpha1);
	}
	if(Legs[legNum].V2Conf.Reversed)
	{
		Legs[legNum].V2 = RadToPulse(-alpha2);
	}
	else
	{
		Legs[legNum].V2 = RadToPulse(alpha2);
	}
	if(Legs[legNum].V3Conf.Reversed)
	{
		Legs[legNum].V3 = RadToPulse(-alpha3);
	}
	else
	{
		Legs[legNum].V3 = RadToPulse(alpha3);
	}
}
