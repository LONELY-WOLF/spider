#ifndef __WALK_LEGACY_H
#define __WALK_LEGACY_H

extern uint8_t Route;

extern uint8_t Now_Route;

extern void (*WalkManager)();

void Step();
void Init_Work();

//extern struct Leg;

#endif
