#include <FastLED.h>
#include <TaskScheduler.h>
#include "BreathingLever.h"

Scheduler runner1;
Scheduler runner2;

void breathingLever();
void breathingHill();

#define NUM_LEDS 180
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

Task effectHill(50, TASK_FOREVER, &breathingHill, &runner1, true);
Task effectLever(50, TASK_FOREVER, &breathingLever, &runner2, true);

void setup() {

  FastLED.addLeds<WS2812B, 3, GRB>(leds, NUM_LEDS);
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
      break;
  }
  
  FastLED.show();
}
