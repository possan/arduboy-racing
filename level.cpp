#include "global.h"
#include "level.h"
#include "levelimages.h"


#define MAP_STRIDE 20

const unsigned char leveldata[400] = {

	0,0,0,7,0, 0,8,0,0,0, 0,0,0,7,0, 0,8,0,0,0,
	0,3,1,1,1, 4,0,9,0,0, 0,3,1,1,1, 4,0,9,0,0,
	0,2,0,0,0, 2,0,0,7,0, 0,2,0,0,0, 2,0,0,7,0,
	0,2,0,0,0, 5,1,1,4,0, 0,2,0,0,0, 5,1,1,4,0,
	0,2,7,0,0, 0,0,0,2,9, 0,2,7,0,0, 0,0,0,2,9,
	0,2,8,7,0, 0,0,0,2,0, 0,2,8,7,0, 0,0,0,2,0,
	0,2,0,9,0, 0,0,0,2,0, 0,2,0,9,0, 0,0,0,2,0,
	0,5,1,1,4, 9,3,1,6,7, 0,5,1,1,4, 9,3,1,6,7,
	0,0,0,0,5, 1,6,0,7,0, 0,0,0,0,5, 1,6,0,7,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

	0,0,0,7,0, 0,8,0,0,0, 0,0,0,7,0, 0,8,0,0,0,
	0,3,1,1,1, 4,0,9,0,0, 0,3,1,1,1, 4,0,9,0,0,
	0,2,0,0,0, 2,0,0,7,0, 0,2,0,0,0, 2,0,0,7,0,
	0,2,0,0,0, 5,1,1,4,0, 0,2,0,0,0, 5,1,1,4,0,
	0,2,7,0,0, 0,0,0,2,9, 0,2,7,0,0, 0,0,0,2,9,
	0,2,8,7,0, 0,0,0,2,0, 0,2,8,7,0, 0,0,0,2,0,
	0,2,0,9,0, 0,0,0,2,0, 0,2,0,9,0, 0,0,0,2,0,
	0,5,1,1,4, 9,3,1,6,7, 0,5,1,1,4, 9,3,1,6,7,
	0,0,0,0,5, 1,6,0,7,0, 0,0,0,0,5, 1,6,0,7,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

};








void level_reset(LEVEL *level) {
	for(int i=0; i<NUMDIRT; i++) {
		level->dirt_x[i] = ((rand() % 50) - 25) * 40;
		level->dirt_y[i] = ((rand() % 50) - 25) * 40;
		level->dirt_t[i] = rand() % 6;
	}

	for(int i=0; i<NUMJUMPS; i++) {
		level->jump_x[i] = ((rand() % 50) - 25) * 50;
		level->jump_y[i] = ((rand() % 50) - 25) * 50;
		level->jump_t[i] = rand() % 2;
	}
}

void level_move(LEVEL *level) {
}

void level_render(LEVEL *level, int camerax, int cameray) {
	int sx = 0, sy = 0;

	// int cxbase = (camerax >> 6) << 6;
	// int cybase = (cameray >> 6) << 6;

	for(int j=0; j<MAP_STRIDE; j++) {
		for(int i=0; i<MAP_STRIDE; i++) {
			int dx = 0 + i * 64;
			int dy = 0 + j * 64;
			if (project_isometric(dx, dy, 0, camerax, cameray, &sx, &sy)) {
				// _arduboy->drawPixel(sx, sy, 1);

				unsigned char *groundtile = NULL;
				unsigned char c = leveldata[j * MAP_STRIDE + i];
				switch(c) {
					case 1: groundtile = __groundH; break;
					case 2: groundtile = __groundV; break;
					case 3: groundtile = __groundC1; break;
					case 4: groundtile = __groundC2; break;
					case 5: groundtile = __groundC3; break;
					case 6: groundtile = __groundC4; break;
					case 7: groundtile = __groundD1; break;
					case 8: groundtile = __groundD2; break;
					case 9: groundtile = __groundD3; break;
				}

				if (groundtile) {
					_arduboy->drawBitmap(sx - 32, sy - 16, groundtile, 64, 32, WHITE);
				}
			}
		}
	}

	/*
	for(int i=0; i<NUMDIRT; i++) {
		int dx = (int)level->dirt_x[i];
		int dy = (int)level->dirt_y[i];
		dx -= cxbase;
		dy -= cxbase;
		dx += 256;
		dy += 256;
		dx %= 256;
		dy %= 256;
		if (project_isometric(dx, dy, 0, camerax, cameray, &sx, &sy)) {
			switch (level->dirt_t[i]) {
				case 0: _arduboy->drawBitmap(sx - 12, sy - 6, __ground1, 24, 16, WHITE); break;
				case 1: _arduboy->drawBitmap(sx - 12, sy - 8, __ground2, 24, 16, WHITE); break;
				case 2: _arduboy->drawBitmap(sx - 12, sy - 8, __ground3, 24, 16, WHITE); break;
				case 3: _arduboy->drawBitmap(sx - 12, sy - 8, __ground4, 24, 16, WHITE); break;
				case 4: _arduboy->drawBitmap(sx - 12, sy - 8, __ground5, 24, 16, WHITE); break;
				case 5: _arduboy->drawBitmap(sx - 12, sy - 8, __ground6, 24, 16, WHITE); break;
			}
		}
	}

	for(int i=0; i<NUMJUMPS; i++) {
		int dx = (int)level->jump_x[i];
		int dy = (int)level->jump_y[i];
		dx -= cxbase;
		dy -= cxbase;
		dx += 256;
		dy += 256;
		dx %= 256;
		dy %= 256;
		if (project_isometric(dx, dy, 0, camerax, cameray, &sx, &sy)) {
			switch (level->jump_t[i]) {
				case 0: _arduboy->drawBitmap(sx - 24, sy - 12, __jump1, 48, 24, WHITE); break;
				case 1: _arduboy->drawBitmap(sx - 24, sy - 12, __jump2, 48, 24, WHITE); break;
			}
		}
	}
	*/
}
