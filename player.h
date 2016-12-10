#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "physics.h"

typedef struct {
	// BODY body;
	ELASTIC x;
	ELASTIC y;
	ELASTIC z;

	ELASTIC speed;
	int direction;
	int speed_direction;

	int speed_delta;
	int direction_delta;
} PLAYER;

extern void player_reset(PLAYER *player, int x, int y);
extern void player_move(PLAYER *player);
extern void player_render(PLAYER *player, int camerax, int cameray);

extern void player_accelerate(PLAYER *player, int acceleration);
extern void player_turn(PLAYER *player, int turning);

#endif
