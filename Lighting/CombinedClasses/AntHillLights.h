/// @file    AntHillLights.h
/// @brief   Class to control the ant stands, hill, and lever

#ifndef ANTHILLLIGHTS_H
#define ANTHILLLIGHTS_H

#include <FastLED.h>

class AntHillLights {
public:
    AntHillLights(int numLeds, int dataPin);
    void setup();
    void setColorInZone(int zone, CRGB color);
    void fadeColorInZone(int zone, CRGB targetColor, int transitionTime);
    void pulseColorInZone(int zone, CRGB color, int pulseTime);

private:
    int numLeds;
    int dataPin;
    CRGB* leds;
    CLEDController* controller;
};

#endif // ANTHILLLIGHTS_H
