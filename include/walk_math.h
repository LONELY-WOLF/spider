#ifndef __WALK_MATH_H
#define __WALK_MATH_H

#include "legs.h"

#define LENGTH_L1 30.0
#define LENGTH_L2 65.0
#define LENGTH_L3 120.0

uint32_t RadToPulse(float angle);
void SetLegPos(int legNum, float lx, float ly, float lz);

#endif
