#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <Arduino.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <avr/power.h>
#include "Arduboy2.h"

extern uint8_t sine_wave[];
extern Arduboy2 *_arduboy;

extern int project_isometric(int ix, int iy, int iz, int cx, int cy, int *ox, int *oy);

#endif
