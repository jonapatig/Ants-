/// @file    LEDControlCircle.h
/// @brief   Class to control an LED ring with animations

#ifndef LEDCONTROLCIRCLE_H
#define LEDCONTROLCIRCLE_H

#include <FastLED.h>

class LEDControlCircle {
public:
    LEDControlCircle(int numLeds, int dataPin);
    void setup();
    void setColor(float startDegree, float endDegree, CRGB color);
    void fadeColor(float startDegree, float endDegree, CRGB targetColor, int transitionTime);
    void pulseColor(float startDegree, float endDegree, CRGB color, int pulseTime);

private:
    int numLeds;
    int dataPin;
    float degreeStep;
    CRGB* leds;
    CLEDController* controller;
};

#endif // LEDCONTROLCircle_H
