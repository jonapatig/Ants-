#include <FastLED.h>
#include <TaskScheduler.h>
#include "AntSelect.h"
#include "CrownLeds.h"

Scheduler runner1;
Scheduler runner2;
Scheduler runner3;
Scheduler resetRunner;

void breathingLever();
void breathingHill();
// void pacifica_loop();
void displayAnt1();
void crownReset();

void reset(){
  crownReset();
}

const int NUM_LEDS_ANTS = 180;
const int DATA_PIN_ANTS = 7;

const int NUM_LEDS_HALO = 96;
const int DATA_PIN_HALO = 5;

const int NUM_LEDS_CROWN = 160;
const int DATA_PIN_CROWN = 6;

const int NUM_LEDS_BRANCH = 22;
const int DATA_PIN_BRANCH = 7;


CRGB ledsAnts[NUM_LEDS_ANTS];
// CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsCrown[NUM_LEDS_CROWN];
// CRGB ledsBranch[NUM_LEDS_CROWN];

Task effectHill(50, TASK_FOREVER, &breathingHill, &runner1, true);
Task effectLever(50, TASK_FOREVER, &breathingLever, &runner2, true);
// Task effectHalo(50, TASK_FOREVER, &pacifica_loop, &runner2, true);
Task effectCrown(50, TASK_FOREVER, &displayAnt1, &runner1, true);
Task effectReset(50, TASK_FOREVER, &reset, &runner2, true);

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN_ANTS, GRB>(ledsAnts, NUM_LEDS_ANTS);
  // FastLED.addLeds<WS2812B, DATA_PIN_HALO, GRB>(ledsHalo, NUM_LEDS_HALO);
  FastLED.addLeds<WS2812B, DATA_PIN_CROWN, GRB>(ledsCrown, NUM_LEDS_CROWN);
  // FastLED.addLeds<WS2811, DATA_PIN_BRANCH, GRB>(ledsBranch, NUM_LEDS_BRANCH);
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
