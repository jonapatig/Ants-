#ifndef ANTSELECT_H
#define ANTSELECT_H

#include <FastLED.h>
#include <Arduino.h>

// Define your zones here if not already defined elsewhere


extern CRGB ledsAnts[]; // Make sure this is declared properly to match your LED setup

void breathingHill();
void breathingLever();


#endif // ANTSELECT_H
