#include "FastLED.h"
#include "Branch.h"

const int numLeds = 22;

void fullBranch() {
  for (int i = 0; i < numLeds; i++) {
    ledsBranch[i] = CRGB::Green; // Equivalent to CHSV(90, 255, 255)
  }
  FastLED.show();
}

void initializeRunners(int numRunners, int runnerPos[], bool runnerDirection[]) {
  bool allZeros = true;
  for (int i = 0; i < numRunners; i++) {
    if (runnerPos[i] != 0) {
      allZeros = false;
      break;
    }
  }

  if (allZeros) {
    for (int i = 0; i < numRunners; i++) {
      runnerPos[i] = random(0, numLeds);
      runnerDirection[i] = random(0, 2) == 0;
    }
  }
}

void updateRunners(int numRunners, int runnerPos[], bool runnerDirection[]) {
  for (int i = 0; i < numRunners; i++) {
    if (runnerDirection[i]) {
      runnerPos[i]++;
      if (runnerPos[i] >= numLeds) {
        runnerPos[i] = numLeds - 1;
        runnerDirection[i] = false;
      }
    } else {
      runnerPos[i]--;
      if (runnerPos[i] < 0) {
        runnerPos[i] = 0;
        runnerDirection[i] = true;
      }
    }
  }
}

void runBranch() {
  const int numRunners = 5;
  static int runnerPos[numRunners] = {0};
  static bool runnerDirection[numRunners] = {false};

  initializeRunners(numRunners, runnerPos, runnerDirection);

  fill_solid(ledsBranch, numLeds, CRGB::Black);

  for (int i = 0; i < numRunners; i++) {
    ledsBranch[runnerPos[i]] = CRGB::Green; // Equivalent to CHSV(90, 255, 255)
    if (runnerPos[i] - 1 >= 0) {
      ledsBranch[runnerPos[i] - 1] = CRGB(128, 255, 128); // Equivalent to CHSV(90, 255, 150)
      if (runnerPos[i] - 2 >= 0) {
        ledsBranch[runnerPos[i] - 2] = CRGB(64, 255, 64); // Equivalent to CHSV(90, 255, 100)
      }
    } else {
      runnerDirection[i] = !runnerDirection[i];
    }

    if (runnerPos[i] + 1 < numLeds) {
      ledsBranch[runnerPos[i] + 1] = CRGB(128, 255, 128); // Equivalent to CHSV(90, 255, 150)
      if (runnerPos[i] + 2 < numLeds) {
        ledsBranch[runnerPos[i] + 2] = CRGB(64, 255, 64); // Equivalent to CHSV(90, 255, 100)
      }
    } else {
      runnerDirection[i] = !runnerDirection[i];
    }
  }

  updateRunners(numRunners, runnerPos, runnerDirection);
  FastLED.show();
}
