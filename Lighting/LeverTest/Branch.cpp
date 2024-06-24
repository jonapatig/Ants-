#include "FastLED.h"
#include "Branch.h"

const int numLeds = 22;

void fullBranch() {
}

void runBranch() {
  const int numRunners = 5;
  static int runnerPos[numRunners];
  static bool runnerDirection[numRunners];

  // NEED FUNCTION TO CHECK IF RUNNER ARRAY IS 0s AND THEN FILL UP WITH RANDOM POSITIONS
  
  for (int i = 0; i < numRunners; i++) {
    if (runnerDirection[i]) {
      ledsBranch[runnerPos[i]] = CHSV(90, 255, 255);
      if (runnerPos[i] - 1 >= 0) {
        ledsBranch[runnerPos[i] - 1] = CHSV(90, 255, 150);
        if (runnerPos[i] - 1 >= 1) {
          ledsBranch[runnerPos[i] - 2] = CHSV(90, 255, 100);
        }
      } else {
        runnerDirection[i] = !runnerDirection[i];
      }
    }

    if (!runnerDirection[i]) {
      ledsBranch[runnerPos[i]] = CHSV(90, 255, 255);
      if (runnerPos[i] + 1 < numRunners) {
        ledsBranch[runnerPos[i] + 1] = CHSV(90, 255, 150);
        if (runnerPos[i] + 1 < numRunners - 1) {
          ledsBranch[runnerPos[i] + 2] = CHSV(90, 255, 100);
        }
      } else {
        runnerDirection[i] = !runnerDirection[i];
      }
    }
  }
  
  // NEED FUNCTION TO INCREMENT RUNNERS DEPDNDING ON IF RUNNER DIRECTION IS TRUE OR FALSE
  
}
