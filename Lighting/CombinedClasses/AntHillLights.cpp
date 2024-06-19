/// @file    AntHillLights.cpp
/// @brief   Implementation of the AntHillLights class

#include "AntHillLights.h"

AntHillLights::AntHillLights(int numLeds, int dataPin) 
    : numLeds(numLeds), dataPin(dataPin) {
    leds = new CRGB[numLeds];
}

void AntHillLights::setup() {
    delay(2000); // sanity check delay - allows reprogramming if accidentally blowing power w/leds

    // Use a runtime function to set the pin dynamically
    switch(dataPin) {
        case 3:
            FastLED.addLeds<WS2812B, 3, GRB>(leds, numLeds);
            break;
        case 4:
            FastLED.addLeds<WS2812B, 4, GRB>(leds, numLeds);
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

void AntHillLights::setColorInZone(int zone, CRGB color) {
    int startLed, endLed;
    
    if (zone == 0) {
        startLed = 0;
        endLed = 32;
    } else if (zone == 1) {
        startLed = 33;
        endLed = 97;
    } else if (zone == 2) {
        startLed = 98;
        endLed = 132;
    } else {
        return; // Invalid zone
    }

    for (int i = startLed; i <= endLed; i++) {
        leds[i] = color;
    }
    FastLED.setBrightness(255);
    FastLED.show();
}

void AntHillLights::fadeColorInZone(int zone, CRGB targetColor, int transitionTime) {
    for (int j = 0; j <= 255; j++) {
        CRGB color = blend(CRGB::Black, targetColor, j);
        setColorInZone(zone, color);
        delay(transitionTime / 255);
    }
}

void AntHillLights::pulseColorInZone(int zone, CRGB color, int pulseTime) {
    for (int j = 0; j <= 255; j++) {
        CRGB pulsingColor = color;
        pulsingColor.nscale8(j);
        setColorInZone(zone, pulsingColor);
        delay(pulseTime / 510);
    }
    for (int j = 255; j >= 0; j--) {
        CRGB pulsingColor = color;
        pulsingColor.nscale8(j);
        setColorInZone(zone, pulsingColor);
        delay(pulseTime / 510);
    }
}

