#ifndef _GAME_H_
#define _GAME_H_

#include "physics.h"
#include "level.h"
#include "player.h"

typedef struct {
	// BODY body;
	LEVEL level;
	PLAYER player;
	ELASTIC camera_x;
	ELASTIC camera_y;
} GAME;

void game_init(GAME *game);
void game_move(GAME *game);
void game_render(GAME *game);

#endif
