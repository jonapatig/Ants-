#include "FastLED.h"
#include "EcoHalo.h"

const int numLeds = 96;
const int spotSize = 13;
const int slowDownValue = 4;

void runHalo(int numSad) {
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
  fill_solid(ledsHalo, numLeds, CHSV(96-(numSad*8), 255, fullBrightness));

  for (int i = 0; i < numLeds; i++) {
    if (ledsBright[i] > 0) {
      ledsBright[i] -= 3;
      ledsHalo[i] = CHSV(80 + colorOffset[i]-(numSad*8), 255, ledsBright[i]);
    }
  }
}

void fullEco() {
  runHalo(1);
}
void damagedEco1() {
  runHalo(7);
}
void damagedEco2() {
  runHalo(10);
}