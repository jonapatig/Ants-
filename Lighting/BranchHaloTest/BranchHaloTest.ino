#include <FastLED.h>
#include <TaskScheduler.h>
#include "EcoHalo.h"
#include "Branch.h"

Scheduler runner1;
Scheduler runner2;


void runBranch();
void branch1();
void branch2();
void fullEco();
void damagedEco1();
void damagedEco2();

const int NUM_LEDS_HALO = 96;
const int DATA_PIN_HALO = 6;

const int NUM_LEDS_BRANCH = 22;
const int DATA_PIN_BRANCH = 5;

CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsBranch[NUM_LEDS_BRANCH];

Task effectBranch(50, TASK_FOREVER, &runBranch, &runner1, true);
Task effectHalo(50, TASK_FOREVER, &fullEco, &runner1, true);
// Task effectHalo(50, TASK_FOREVER, &pacifica_loop, &runner2, true);
Task effectDamagedBranch(50, TASK_FOREVER, &runBranch, &runner2, true);
Task effectDamagedHalo(50, TASK_FOREVER, &damagedEco1, &runner2, true);

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN_HALO, GRB>(ledsHalo, NUM_LEDS_HALO);
  FastLED.addLeds<WS2811, DATA_PIN_BRANCH, BRG>(ledsBranch, NUM_LEDS_BRANCH);
  FastLED.setBrightness(50);
}

void loop() {
  static uint32_t lastSwitchTime = 0;
  uint32_t currentTime = millis();
  static int state = 0; // 0 for runner1, 1 for runner2

  // Check if 5 seconds have passed
  if (currentTime - lastSwitchTime >= 15000) {
    state = (state + 1) % 2;
    lastSwitchTime = currentTime;
  }

  // Execute the appropriate runner based on the state
  switch (state) {
    case 0:
      runner1.execute();
      break;
    case 1:
      runner2.execute();

  }
  // runner3.execute();
  
  FastLED.show();
}
