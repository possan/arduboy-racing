#include "physics.h"

#define VELOCITY_DECAY 128
#define VELOCITY_MULTIPLIER 64

#define ELASTIC_INFLUENCE 32
#define ELASTIC_FEEDBACK 32

// void body_reset(BODY *body, int x, int y) {
// 	body->px = x * PHYSICS_MULTIPLIER;
// 	body->py = y * PHYSICS_MULTIPLIER;
// 	body->vx = 0;
// 	body->vy = 0;
// 	body->fx = 0;
// 	body->fy = 0;
// 	body->velocity_feedback = VELOCITY_MULTIPLIER;
// 	body->velocity_decay = VELOCITY_DECAY;
// }

// void body_add_force(BODY *body, int x, int y) {
// 	body->fx += x * PHYSICS_MULTIPLIER;
// 	body->fy += y * PHYSICS_MULTIPLIER;
// }

// void body_move(BODY *body) {
// 	body->vx = (body->vx * body->velocity_decay) / PHYSICS_MULTIPLIER;
// 	body->vy = (body->vy * body->velocity_decay) / PHYSICS_MULTIPLIER;
// 	body->vx += body->fx;
// 	body->vy += body->fy;
// 	body->px += (body->vx * body->velocity_feedback) / PHYSICS_MULTIPLIER;
// 	body->py += (body->vy * body->velocity_feedback) / PHYSICS_MULTIPLIER;
// 	body->fx = 0;
// 	body->fy = 0;
// }

// void body_get_position(BODY *b, int *x, int *y) {
// 	*x = b->px / PHYSICS_MULTIPLIER;
// 	*y = b->py / PHYSICS_MULTIPLIER;
// }

void elastic_reset(ELASTIC *elastic, int value) {
	elastic->value = value * PHYSICS_MULTIPLIER;
	elastic->force = 0;
	elastic->velocity = 0;
	elastic->velocity_influence = ELASTIC_INFLUENCE;
	elastic->velocity_feedback = ELASTIC_FEEDBACK;
}

// void elastic_set_decay(ELASTIC *elastic, int value) {
// 	elastic->decay = value;
// }

// void elastic_set_feedback(ELASTIC *elastic, int value) {
// 	elastic->feedback = value;
// }

void elastic_add_force(ELASTIC *elastic, int value) {
	elastic->force += value * PHYSICS_MULTIPLIER;
}

void elastic_go_to(ELASTIC *elastic, int value) {
	int delta = value - (elastic->value / PHYSICS_MULTIPLIER);
	elastic_add_force(elastic, delta);
}


// void elastic_set_current(ELASTIC *elastic, int value) {
// 	elastic->value = value * PHYSICS_MULTIPLIER;
// }

// void elastic_set_target(ELASTIC *elastic, int value) {
// 	elastic->target = value * PHYSICS_MULTIPLIER;
// }

void elastic_move(ELASTIC *elastic) {
	// int delta = elastic->target - elastic->value;
	// elastic->value += (delta * elastic->decay) / PHYSICS_MULTIPLIER;

	elastic->velocity = (elastic->velocity * elastic->velocity_feedback) / PHYSICS_MULTIPLIER;
	elastic->velocity += elastic->force;
	elastic->value += (elastic->velocity * elastic->velocity_influence) / PHYSICS_MULTIPLIER;
	elastic->force = 0;
}

int elastic_get_value(ELASTIC *elastic) {
	return elastic->value / PHYSICS_MULTIPLIER;
}
