/// @file    LEDControlCircle.h
/// @brief   Class to control an LED ring with animations

#ifndef LEDCONTROLCIRCLE_H
#define LEDCONTROLCIRCLE_H

#include <FastLED.h>
#include <LinkedList.h>

class LEDControlCircle {
public:
    LEDControlCircle(int numLeds, int dataPin);
    void setup();
    void setColor(float startDegree, float endDegree, CRGB color);
    void fadeColor(float startDegree, float endDegree, CRGB targetColor, int transitionTime, unsigned long currentMillis);
    void pulseColor(float startDegree, float endDegree, CRGB color, int pulseTime, unsigned long currentMillis);
    void update(unsigned long currentMillis);

private:
    int numLeds;
    int dataPin;
    float degreeStep;
    CRGB* leds;
    CLEDController* controller;

    struct FadeState {
        unsigned long startMillis;
        int step;
        float startDegree;
        float endDegree;
        CRGB targetColor;
        int transitionTime;
    };

    struct PulseState {
        unsigned long startMillis;
        int step;
        bool increasing;
        float startDegree;
        float endDegree;
        CRGB color;
        int pulseTime;
    };

    LinkedList<FadeState> fadeStates;
    LinkedList<PulseState> pulseStates;

    void updateFade(unsigned long currentMillis);
    void updatePulse(unsigned long currentMillis);
    void delayWithoutBlocking(unsigned long interval, unsigned long startMillis);
};

#endif // LEDCONTROLCIRCLE_H
