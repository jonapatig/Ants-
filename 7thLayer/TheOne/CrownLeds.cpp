#include "FastLED.h"
#include "CrownLeds.h"

int NUM_LEDS = 155;
static int brightness[5] = {0, 0, 0, 0, 0};


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
    static int direction[5] = {10, 8, 6, 4, 2};
    unsigned long currentTime = millis();

    if (currentTime - lastTime >= 100) {
        for (int i = 0; i < 5; i++) {
            if (brightness[i] < 255) {
                brightness[i] += direction[i];
                brightness[i] = constrain(brightness[i], 0, 255); // Ensure brightness is within bounds
            }
        }
        lastTime = currentTime;
    }

    // Calculate total LEDs to fill based on the percentage
    int totalLedsToFill = round(NUM_LEDS * percentage);
    int currentLed = 0;

    for (int i = 0; i < 5; i++) {
        float rowPercentage = (float)totalLedsToFill / rows[i];
        rowPercentage = constrain(rowPercentage, 0.0, 1.0);

        CRGB fadedColor = color;
        fadedColor.fadeToBlackBy(255 - brightness[i]);

        fillRow(currentLed, rows[i], rowPercentage, fadedColor, brightness[i]);

        totalLedsToFill -= rows[i] * rowPercentage;
        currentLed += rows[i];
    }
}

void displayAntA() {
    myPercentage(0.005, CRGB::Gold, 5000);
}

void displayAntR() {
    myPercentage(0.98, CRGB::Gold, 5000);
}

void displayAntY() {
    myPercentage(0.02, CRGB::Gold, 5000);
}
void crownReset() {
    static uint32_t lastTime = 0;
    static int rows[5] = {31, 32, 32, 32, 31};
    static int direction[5] = {2, 4, 6, 8, 10};
    static bool resetInProgress = false;
    unsigned long currentTime = millis();

    if (!resetInProgress) {
        lastTime = currentTime;
        resetInProgress = true;
        for (int i = 0; i < 5; i++) {
            brightness[i] = 255; // Start from full brightness
        }
    }

    if (currentTime - lastTime >= 100) {
        bool allRowsDimmed = true;

        for (int i = 0; i < 5; i++) {
            if (brightness[i] > 0) {
                brightness[i] -= direction[i];
                brightness[i] = constrain(brightness[i], 0, 255); // Ensure brightness is within bounds
                allRowsDimmed = false;
            }
        }

        int currentLed = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < rows[i]; j++) {
                ledsCrown[currentLed + j].fadeLightBy(255 - brightness[i]);
            }
            currentLed += rows[i];
        }

        lastTime = currentTime;

        if (allRowsDimmed) {
            resetInProgress = false; // Reset is complete
        }
    }
}

// void crownReset(){
//     static int rows[5] = {31, 32, 32, 32, 31};

//     int currentLed = 0;
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < rows[i]; j++) {
//             ledsCrown[currentLed + j] = CRGB::Black;

//         }
//         currentLed += rows[i];
//         brightness[i] = 0;
//     }
//     FastLED.show();