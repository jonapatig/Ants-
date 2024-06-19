/// @file    LEDControlCircle.cpp
/// @brief   Implementation of the LEDControlCircle class

#include "LEDControlCircle.h"
#include <math.h>

LEDControlCircle::LEDControlCircle(int numLeds, int dataPin) 
    : numLeds(numLeds), dataPin(dataPin), degreeStep(360.0 / numLeds), fadeStates(), pulseStates() {
    leds = new CRGB[numLeds];
}

void LEDControlCircle::setup() {
    delay(2000); // sanity check delay - allows reprogramming if accidentally blowing power w/leds

    // Use a runtime function to set the pin dynamically
    switch(dataPin) {
        case 3:
            FastLED.addLeds<WS2812B, 3, GRB>(leds, numLeds);
            break;
        case 4:
            FastLED.addLeds<WS2812B, 4, GRB>(leds, numLeds);
            break;
        // Add more cases as needed for other pins
        default:
            // Handle invalid pin or add more cases as needed
            break;
    }
}

void LEDControlCircle::setColor(float startDegree, float endDegree, CRGB color) {
    // Ensure degrees are within 0-360 range
    startDegree = fmod(startDegree, 360.0);
    endDegree = fmod(endDegree, 360.0);

    if (startDegree < 0) startDegree += 360;
    if (endDegree < 0) endDegree += 360;

    // Handle wrap-around cases
    if (startDegree > endDegree) {
        setColor(startDegree, 360.0, color);
        setColor(0, endDegree, color);
        return;
    }

    int startIndex = floor(startDegree / degreeStep);
    int endIndex = ceil(endDegree / degreeStep);

    // If endDegree is exactly 360, we need to set it to cover the full circle
    if (endDegree == 360.0) {
        endIndex = numLeds - 1;
    }

    for (int i = startIndex; i <= endIndex && i < numLeds; i++) {
        leds[i % numLeds] = color;
    }

    FastLED.show();
}

void LEDControlCircle::fadeColor(float startDegree, float endDegree, CRGB targetColor, int transitionTime, unsigned long currentMillis) {
    FadeState newState = {currentMillis, 0, startDegree, endDegree, targetColor, transitionTime};
    fadeStates.add(newState);
}

void LEDControlCircle::pulseColor(float startDegree, float endDegree, CRGB color, int pulseTime, unsigned long currentMillis) {
    PulseState newState = {currentMillis, 0, true, startDegree, endDegree, color, pulseTime};
    pulseStates.add(newState);
}

void LEDControlCircle::update(unsigned long currentMillis) {
    updateFade(currentMillis);
    updatePulse(currentMillis);
}

void LEDControlCircle::updateFade(unsigned long currentMillis) {
    for (int i = 0; i < fadeStates.size(); i++) {
        FadeState &state = fadeStates.get(i);
        if (currentMillis - state.startMillis >= (unsigned long)(state.transitionTime / 255)) {
            state.startMillis = currentMillis;
            if (state.step <= 255) {
                CRGB color = blend(CRGB::Black, state.targetColor, state.step);
                setColor(state.startDegree, state.endDegree, color);
                state.step++;
            } else {
                fadeStates.remove(i);
                i--;
            }
        }
    }
}

void LEDControlCircle::updatePulse(unsigned long currentMillis) {
    for (int i = 0; i < pulseStates.size(); i++) {
        PulseState &state = pulseStates.get(i);
        if (currentMillis - state.startMillis >= (unsigned long)(state.pulseTime / 510)) {
            state.startMillis = currentMillis;
            if (state.increasing) {
                if (state.step <= 255) {
                    CRGB pulsingColor = state.color;
                    pulsingColor.nscale8(state.step);
                    setColor(state.startDegree, state.endDegree, pulsingColor);
                    state.step++;
                } else {
                    state.increasing = false;
                }
            } else {
                if (state.step >= 0) {
                    CRGB pulsingColor = state.color;
                    pulsingColor.nscale8(state.step);
                    setColor(state.startDegree, state.endDegree, pulsingColor);
                    state.step--;
                } else {
                    state.increasing = true;
                    pulseStates.remove(i);
                    i--;
                }
            }
        }
    }
}

void LEDControlCircle::delayWithoutBlocking(unsigned long interval, unsigned long startMillis) {
    while (millis() - startMillis < interval) {
        // You can add code here to handle other tasks if needed
    }
}
