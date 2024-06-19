#ifndef BREATHINGLEVER_H
#define BREATHINGLEVER_H

#include <FastLED.h>
#include <Arduino.h>

// Define your zones here if not already defined elsewhere
#define ZONE1_START 0
#define ZONE1_END 97
#define ZONE2_START 98
#define ZONE2_END 129
#define ZONE3_START 130
#define ZONE3_END 149

extern CRGB leds[]; // Make sure this is declared properly to match your LED setup

void breathingHill();
void breathingLever();


#endif // BREATHINGLEVER_H
