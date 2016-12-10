#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#define PHYSICS_MULTIPLIER 128

// typedef struct {
//   long vx;
//   long vy;
//   long fx;
//   long fy;
//   long px;
//   long py;
//   long velocity_feedback;
//   long velocity_decay;
// } BODY;

// extern void body_reset(BODY *b, int x, int y);
// extern void body_move(BODY *b);
// extern void body_get_position(BODY *b, int *x, int *y);
// extern void body_add_force(BODY *b, int x, int y);

typedef struct {
  long value;
  long force;
  long velocity;
  // long target;
  long velocity_feedback;
  long velocity_influence;
} ELASTIC;

extern void elastic_reset(ELASTIC *b, int value);
extern void elastic_add_force(ELASTIC *elastic, int value);
extern void elastic_go_to(ELASTIC *elastic, int value);
extern void elastic_move(ELASTIC *elastic);
extern int elastic_get_value(ELASTIC *elastic);

#endif
