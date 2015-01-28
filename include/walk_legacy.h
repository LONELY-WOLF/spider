#ifndef __WALK_LEGACY_H
#define __WALK_LEGACY_H

extern uint8_t Route;

extern uint8_t Now_Route;

#define ROUTE_STOP 0
#define ROUTE_FORWARD 1
#define ROUTE_BACK 2
#define ROUTE_RIGHT 3
#define ROUTE_LEFT 4

extern void (*WalkManager)();

void Step();
void Init_Work();

//extern struct Leg;

#endif
