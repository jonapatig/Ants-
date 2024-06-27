#include "FastLED.h"
#include "EcoHalo.h"

const int numLeds = 96;
const int spotSize = 13;
const int slowDownValue = 4;

void runHalo(int numSad) {
  static int counter = 0;
  static bool raise = false;
  static int ledsBright[numLeds];
  static int colorOffset[numLeds];

  // Calculate brightness based on numSad
  int fullBrightness = 70 - (numSad * 5);
  fullBrightness = constrain(fullBrightness, 0, 255); // Ensure brightness is within valid range

  if (int(random(0, numSad)) == 0) {
    int selectedLed = int(random(0, numLeds));
    ledsBright[selectedLed] = 255;
    colorOffset[selectedLed] = random(-10, 15);
  }
  fill_solid(ledsHalo, numLeds, CHSV(96, 255, fullBrightness));

  for (int i = 0; i < numLeds; i++) {
    if (ledsBright[i] > 0) {
      ledsBright[i] -= 3;
      ledsHalo[i] = CHSV(80 + colorOffset[i], 255, ledsBright[i]);
    }
  }
  FastLED.show();
}

void fullEco() {
  runHalo(1);
}

void damagedEco1() {
  runHalo(5);
}

void damagedEco2() {
  runHalo(10);
}
