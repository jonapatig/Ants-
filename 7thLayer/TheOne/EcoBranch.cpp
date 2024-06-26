#include <FastLED.h>
#include "EcoBranch.h"

// Define the size of the LED array
const int numLeds = 96;
CRGB ledsBranch[numLeds];

const int spotSize = 13;
const int slowDownValue = 4;

void runEcoBranch(int numSad) {
    static int fullBrightness = 70;
    static int counter = 0;
    static bool raise = false;
    static int ledsBright[numLeds];
    static int colorOffset[numLeds];

    if (int(random(0, numSad)) == 0) {
        int selectedLed = int(random(0, numLeds));
        ledsBright[selectedLed] = 255;
        colorOffset[selectedLed] = random(-10, 15);
    }
    fill_solid(ledsBranch, numLeds, CHSV(96, 255, fullBrightness));

    for (int i = 0; i < numLeds; i++) {
        if (ledsBright[i] > 0) {
            ledsBright[i] -= 3;
            ledsBranch[i] = CHSV(80 + colorOffset[i], 255, ledsBright[i]);
        }
    }
    FastLED.show();
}

void fullEcoBranch() {
    runEcoBranch(1);
}

void damagedEcoBranch1() {
    runEcoBranch(5);
}

void damagedEcoBranch2() {
    runEcoBranch(10);
}
