#include "global.h"
#include "player.h"
#include "playerimages.h"
#include "playerimages2.h"

void player_reset(PLAYER *player, int x, int y) {
	// body_reset(&player->body, x, y);
	// player->body.velocity_feedback = 100;
	// player->body.velocity_decay = 100;

	elastic_reset(&player->x, x);
	player->x.velocity_feedback = 110;
	player->x.velocity_influence = 10;

	elastic_reset(&player->y, y);
	player->y.velocity_feedback = 110;
	player->y.velocity_influence = 10;

	elastic_reset(&player->z, 0);
	player->z.velocity_feedback = 100;
	player->z.velocity_influence = 5;

	elastic_reset(&player->speed, 0);
	player->speed.velocity_feedback = 19;
	player->speed.velocity_influence = 5;

	player->direction = 0;
	player->speed_delta = 0;
	player->direction_delta = 0;
	player->speed_direction = 0;
}

void player_move(PLAYER *player) {
	elastic_move(&player->speed);
	elastic_move(&player->x);
	elastic_move(&player->y);

	elastic_move(&player->z);
	if (player->z.value < 0) {
		player->z.value = 0;
		// bounce of ground
		player->z.velocity = abs(player->z.velocity);
		player->z.force = abs(player->z.force);
	}
	// body_move(&player->body);

	elastic_go_to(&player->z, 0);

	int m = elastic_get_value(&player->speed);

	player->direction += player->direction_delta * (1 + (m / 5));
	if (player->direction >= 256) player->direction -= 256;
	if (player->direction < 0) player->direction += 256;

	if (player->speed_delta > 0) {
		elastic_go_to(&player->speed, 16);
	} else if (player->speed_delta < 0) {
		elastic_go_to(&player->speed, -4);
		elastic_add_force(&player->z, 20);
	} else {
		elastic_go_to(&player->speed, 0);
	}

	int a = player->speed_direction;
	int fx = (m * (sine_wave[(a + 64) & 255] - 128)) / 256;
	int fy = (m * (sine_wave[(a) & 255] - 128)) / 256;
	// body_add_force(&player->body, fx, fy);
	elastic_add_force(&player->x, fx);
	elastic_add_force(&player->y, fy);
}

void player_accelerate(PLAYER *player, int acceleration) {
	player->speed_delta = acceleration;
	if (acceleration) {
		player->speed_direction = (player->direction + 512) & 255;
	}
}

void player_turn(PLAYER *player, int turning) {
	player->direction_delta = turning;
}

void player_render(PLAYER *player, int camerax, int cameray) {
	// int bx = 0, by = 0;
	// body_get_position(&player->body, &bx, &by);
	int bx = elastic_get_value(&player->x);
	int by = elastic_get_value(&player->y);
	int bz = elastic_get_value(&player->z);

	int m = elastic_get_value(&player->speed);

	_arduboy->fillRect(player->direction >> 2, 60, 1, 4, WHITE);

	// _arduboy->fillRect(108 + player->body.fx / 256, 20 + player->body.fy / 256, 2, 2, WHITE);
	// _arduboy->fillRect(64 + player->body.px / 128, 32 + player->body.py / 128, 2, 2, WHITE);
	// _arduboy->fillRect(96 + player->body.vx / 128, 32 + player->body.vy / 128, 2, 2, WHITE);

	int a = player->direction;
	int fx = (sine_wave[(a + 32 + 64) & 255] - 128) / 8;
	int fy = (sine_wave[(a + 32) & 255] - 128) / 16;
	_arduboy->drawLine(64, 32, 64 + fx, 32 + fy);

	char buf[100];

	// sprintf(buf, "px:%d py:%d", (int)(player->body.px / 256), (int)(player->body.py / 256));
	// _arduboy->setCursor(0,0);
 // 	_arduboy->print(buf);

	// sprintf(buf, "fx:%d fy:%d", (int)player->body.fx, (int)player->body.fy);
	// _arduboy->setCursor(0,10);
 // 	_arduboy->print(buf);

	// sprintf(buf, "vx:%d vy:%d", (int)player->body.vx, (int)player->body.vy);
	// _arduboy->setCursor(0,40);
 // 	_arduboy->print(buf);

	// sprintf(buf, "a:%d s:%d", a, m);
	// _arduboy->setCursor(0,50);
 // 	_arduboy->print(buf);

	// sprintf(buf, "%d, %d", player->body.px / 256, player->body.py / 256);
	// _arduboy->setCursor(0,0);
 // 	_arduboy->print(buf);

	// sprintf(buf, "%d, %d", player->body.px / 256, player->body.py / 256);
	// _arduboy->setCursor(0,0);
 // 	_arduboy->print(buf);

	int sx = 0, sy = 0;
	if (project_isometric(bx, by, bz, camerax, cameray, &sx, &sy)) {
		// if (player->z.velocity > 10) {
		// 	_arduboy->drawBitmap(sx - 24, sy - 16, __car2, 48, 32, WHITE);
		// } else if (player->z.velocity < -10) {
		// 	_arduboy->drawBitmap(sx - 24, sy - 16, __car3, 48, 32, WHITE);
		// } else {

		int dd = (a * 19 / 256) % 19;

		PROGMEM const unsigned char *carimg = NULL;

		switch (dd) {
			case 0:  carimg = __car00; break;
			case 1:  carimg = __car01; break;
			case 2:  carimg = __car02; break;
			case 3:  carimg = __car03; break;
			case 4:  carimg = __car04; break;
			case 5:  carimg = __car05; break;
			case 6:  carimg = __car06; break;
			case 7:  carimg = __car07; break;
			case 8:  carimg = __car08; break;
			case 9:  carimg = __car09; break;
			case 10: carimg =  __car10; break;
			case 11: carimg =  __car11; break;
			case 12: carimg =  __car12; break;
			case 13: carimg =  __car13; break;
			case 14: carimg =  __car14; break;
			case 15: carimg =  __car15; break;
			case 16: carimg =  __car16; break;
			case 17: carimg =  __car17; break;
			case 18: carimg =  __car18; break;
		}

		_arduboy->drawBitmap(sx - 16, sy - 12, carimg, 32, 24, WHITE);

		// }
	}

	// speedometer
	_arduboy->fillRect(0, 61, 64, 3, BLACK);
	_arduboy->fillRect(16, 62, 16 + m, 2, WHITE);
}
