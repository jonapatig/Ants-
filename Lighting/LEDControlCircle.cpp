/// @file    LEDControlCircle.cpp
/// @brief   Implementation of the LEDControlCircle class

#include "LEDControlCircle.h"

LEDControlCircle::LEDControlCircle(int numLeds, int dataPin) 
    : numLeds(numLeds), dataPin(dataPin), degreeStep(360.0 / numLeds) {
    leds = new CRGB[numLeds];
}

void LEDControlCircle::setup() {
    delay(2000); // sanity check delay - allows reprogramming if accidentally blowing power w/leds

    // Use a runtime function to set the pin dynamically
    switch(dataPin) {
        case 3:
            FastLED.addLeds<WS2812B, 3, GRB>(leds, numLeds);
            break;
        case 5:
            FastLED.addLeds<WS2812B, 5, GRB>(leds, numLeds);
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

    int startIndex = round(startDegree / degreeStep);
    int endIndex = round(endDegree / degreeStep);

    // If endDegree is exactly 360, we need to set it to cover the full circle
    if (endDegree == 360.0) {
        endIndex = numLeds - 1;
    }

    for (int i = startIndex; i <= endIndex; i++) {
        leds[i % numLeds] = color;
    }

    FastLED.show();
}

void LEDControlCircle::fadeColor(float startDegree, float endDegree, CRGB targetColor, int transitionTime) {
    for (int j = 0; j <= 255; j++) {
        CRGB color = blend(CRGB::Black, targetColor, j);
        setColor(startDegree, endDegree, color);
        delay(transitionTime / 255);
    }
}

void LEDControlCircle::pulseColor(float startDegree, float endDegree, CRGB color, int pulseTime) {
    for (int j = 0; j <= 255; j++) {
        CRGB pulsingColor = color;
        pulsingColor.nscale8(j);
        setColor(startDegree, endDegree, pulsingColor);
        delay(pulseTime / 510);
    }
    for (int j = 255; j >= 0; j--) {
        CRGB pulsingColor = color;
        pulsingColor.nscale8(j);
        setColor(startDegree, endDegree, pulsingColor);
        delay(pulseTime / 510);
    }
}
