#include "game.h"
#include "global.h"
#include "physics.h"

void game_init(GAME *game) {

	// reset level
	level_reset(&game->level);

	// reset player
	player_reset(&game->player, 128, 64);

	// reset camera
	elastic_reset(&game->camera_x, 0);
	elastic_reset(&game->camera_y, 0);

	// elastic_set_decay(&game->camera_x, 90);
	// elastic_set_decay(&game->camera_y, 140);


}

void game_move(GAME *game) {

	// check buttons

	int accel = 0;
	if (_arduboy->pressed(A_BUTTON)) { accel = 1; }
	if (_arduboy->pressed(B_BUTTON)) { accel = -1; }
	player_accelerate(&game->player, accel);

	int turn = 0;
	if (_arduboy->pressed(LEFT_BUTTON)) { turn = -1; }
	if (_arduboy->pressed(RIGHT_BUTTON)) { turn = 1; }
	player_turn(&game->player, turn);

	// update where camera target ...
	// int cx = 0, cy = 0;
	int cx = elastic_get_value(&game->player.x);
	int cy = elastic_get_value(&game->player.y);
	// body_get_position(&game->player.body, &cx, &cy);
	elastic_go_to(&game->camera_x, cx);
	elastic_go_to(&game->camera_y, cy);

	// update physics

	level_move(&game->level);
	player_move(&game->player);
	elastic_move(&game->camera_x);
	elastic_move(&game->camera_y);
}

void game_render(GAME *game) {

	int cx = elastic_get_value(&game->camera_x);
	int cy = elastic_get_value(&game->camera_y);

	// cx = 0;
	// cy = 0;

	// _arduboy->fillRect(0, 0, rand() % 32, 2, WHITE);

	level_render(&game->level, cx, cy);
	player_render(&game->player, cx, cy);
}
