#ifndef PACIFICA_H
#define PACIFICA_H

#include <FastLED.h>

extern CRGB ledsHalo[];
// Function prototypes

void pacifica_loop();
void pacifica_one_layer(CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff);
void pacifica_add_whitecaps();
void pacifica_deepen_colors();

#endif // PACIFICA_H
