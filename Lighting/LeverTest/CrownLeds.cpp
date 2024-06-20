#include "FastLED.h"
#include "CrownLeds.h"

void fillRow(int startIdx, int numLeds, float percentage, CRGB color, uint8_t brightness) {
    int ledsToFill = round(numLeds * percentage);
    int center = numLeds / 2;
    int left = center - (ledsToFill / 2);
    int right = center + (ledsToFill / 2) - 1; // Adjust right to be inclusive

    for (int i = 0; i < numLeds; i++) {
        if (i >= left && i <= right) {
            ledsCrown[startIdx + i] = color;
            ledsCrown[startIdx + i].fadeLightBy(255 - brightness); // Apply fade
        } else {
            ledsCrown[startIdx + i] = CRGB::Black;
        }
    }
}

void myPercentage(float percentage, CRGB color, unsigned long int duration) {
    static int rows[5] = {31, 32, 32, 32, 31};
    static uint32_t lastTime = 0;
    static int brightness[5] = {0, 0, 0, 0, 0};
    static int direction[5] = {5, 5, 5, 5, 5};
    unsigned long currentTime = millis();

    if (currentTime - lastTime >= 20) {
        for (int i = 0; i < 5; i++) {
            if (brightness[i] < 255) {
                brightness[i] += direction[i];
                brightness[i] = constrain(brightness[i], 0, 255); // Ensure brightness is within bounds
            }
        }
        lastTime = currentTime;
    }

    int currentLed = 0;
    for (int i = 0; i < 5; i++) {
        CRGB fadedColor = color;
        fadedColor.fadeToBlackBy(255 - brightness[i]);
        for (int j = 0; j < rows[i]; j++) {
            ledsCrown[currentLed + j] = fadedColor;
        }
        currentLed += rows[i];
    }
}

void displayAnt1() {
    myPercentage(0.7, CRGB::Blue, 5000);
    // displayPercentage(0.7, CRGB::Blue);
}

void crownReset(){
    static int rows[5] = {31, 32, 32, 32, 31};

    int currentLed = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < rows[i]; j++) {
            ledsCrown[currentLed + j] = CRGB::Black;
        }
        currentLed += rows[i];
    }
}