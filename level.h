#ifndef _LEVEL_H_
#define _LEVEL_H_

#define NUMDIRT 40
#define NUMJUMPS 10

typedef struct {
	// BODY body;
	int dirt_x[NUMDIRT];
	int dirt_y[NUMDIRT];
	unsigned char dirt_t[NUMDIRT];

	int jump_x[NUMJUMPS];
	int jump_y[NUMJUMPS];
	unsigned char jump_t[NUMJUMPS];
} LEVEL;

extern void level_reset(LEVEL *LEVEL);
extern void level_move(LEVEL *LEVEL);
extern void level_render(LEVEL *LEVEL, int camerax, int cameray);

#endif
