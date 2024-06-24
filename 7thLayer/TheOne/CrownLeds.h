#ifndef CROWNLEDS_H
#define CROWNLEDS_H

#include <FastLED.h>
#include <Arduino.h>
#include <math.h>

// Define the number of LEDs in each row

extern CRGB ledsCrown[];

void crownReset();
void diplayAntA();
void diplayAntR();
void diplayAntY();
#endif // CROWNLEDS_H
