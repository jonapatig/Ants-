#include <Arduino.h>
#include <FastLED.h>

#include "AntSelect.h"
#include "CrownLeds.h"
#include "EcoHalo.h"
#include "Branch.h"
#include "ContinentSegment.h"

const int leverPin = 22;          // Lever
const int rfid1 = 23;             // Ant A
const int rfid2 = 24;             // Ant Y
const int rfid3 = 25;             // Ant R

// Declare a Segment object globally
ContinentSegment MEX(14, 15);
ContinentSegment NSA(3, 2);
ContinentSegment SSA(5, 4);
ContinentSegment EU(7, 6);
ContinentSegment SA(9, 8);
ContinentSegment SEA(11, 10);
ContinentSegment AUS(13, 12);

// Function declarations
void breathingLever();
void breathingHill();
void displayAntA();
void displayAntR();
void displayAntY();
void crownReset();

// LED Definitions
const int NUM_LEDS_ANTS = 180;
const int DATA_PIN_ANTS = 18;

const int NUM_LEDS_HALO = 96;
const int DATA_PIN_HALO = 19;

const int NUM_LEDS_CROWN = 160;
const int DATA_PIN_CROWN = 20;

const int NUM_LEDS_BRANCH = 22;
const int DATA_PIN_BRANCH = 21;

CRGB ledsAnts[NUM_LEDS_ANTS];
CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsCrown[NUM_LEDS_CROWN];
CRGB ledsBranch[NUM_LEDS_BRANCH];

bool currentLeverState;

int currentState = 0;
static int state = 0;

// Task Functions
void codeReset(uint32_t currentTime) {
  if (state != currentState) {
    switch (state) {
      case 1:
        SSA.toggleMove(currentTime);
        break;
      case 2:
        SSA.toggleMove(currentTime);
        NSA.toggleMove(currentTime);
        break;
      case 3:
        SEA.toggleMove(currentTime);
        break;
      case 4:
        SSA.toggleMove(currentTime);
        MEX.toggleMove(currentTime);
        NSA.toggleMove(currentTime);
        EU.toggleMove(currentTime);
        SA.toggleMove(currentTime);
        AUS.toggleMove(currentTime);
        break;
      case 5:
        SSA.toggleMove(currentTime);
        NSA.toggleMove(currentTime);
        MEX.toggleMove(currentTime);
        SEA.toggleMove(currentTime);
        AUS.toggleMove(currentTime);
        break;
      case 6:
        SEA.toggleMove(currentTime);
        MEX.toggleMove(currentTime);
        SA.toggleMove(currentTime);
        AUS.toggleMove(currentTime);
        break;
    }
    Serial.println(state);
    currentState = state;
    crownReset();
  }
  delay(20);
}

void codeIdle(uint32_t currentTime) {
  codeReset(currentTime);
  breathingHill();
}

void codeIdleA(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SSA.toggleMove(currentTime);
  }
  breathingLever();
  delay(20);
}

void codeIdleR(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SSA.toggleMove(currentTime);
    NSA.toggleMove(currentTime);
  }
  breathingLever();
  delay(20);
}

void codeIdleY(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SEA.toggleMove(currentTime);
  }
  breathingLever();
  delay(20);
}

void codeActiveA(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(currentTime);
    NSA.toggleMove(currentTime);
    EU.toggleMove(currentTime);
    SA.toggleMove(currentTime);
    AUS.toggleMove(currentTime);
  }
  displayAntA();
  delay(20);
}

void codeActiveR(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(currentTime);
    SEA.toggleMove(currentTime);
    AUS.toggleMove(currentTime);
  }
  displayAntR();
  delay(20);
}

void codeActiveY(uint32_t currentTime) {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(currentTime);
    SA.toggleMove(currentTime);
    AUS.toggleMove(currentTime);
  }
  displayAntY();
  delay(20);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup Initialized");

  currentLeverState = !digitalRead(leverPin);

  // External Arduino Setup
  pinMode(leverPin, INPUT);
  pinMode(rfid1, INPUT);
  pinMode(rfid2, INPUT);
  pinMode(rfid3, INPUT);

  // Servo Setup
  pinMode(15, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  MEX.begin();
  NSA.begin();
  SSA.begin();
  EU.begin();
  SA.begin();
  SEA.begin();
  AUS.begin();

  // LED Setup
  FastLED.addLeds<WS2812B, DATA_PIN_ANTS, GRB>(ledsAnts, NUM_LEDS_ANTS);
  FastLED.addLeds<WS2812B, DATA_PIN_HALO, GRB>(ledsHalo, NUM_LEDS_HALO);
  FastLED.addLeds<WS2812B, DATA_PIN_CROWN, GRB>(ledsCrown, NUM_LEDS_CROWN);
  FastLED.addLeds<WS2812B, DATA_PIN_BRANCH, GRB>(ledsBranch, NUM_LEDS_BRANCH);
  FastLED.setBrightness(50);

  delay(500);
}

void loop() {
  static uint32_t lastSwitchTime = 0;
  uint32_t currentTime = millis();

  bool lever = digitalRead(leverPin);
  bool ant1 = digitalRead(rfid1);
  bool ant2 = digitalRead(rfid2);
  bool ant3 = digitalRead(rfid3);

  // Decide which runmode to do
  if (ant1 || ant2 || ant3) {
    if (lever != currentLeverState) {
      if (ant1) {
        state = 4;
      } else if (ant2) {
        state = 5;
      } else if (ant3) {
        state = 6;
      }
    } else {
      if (ant1) {
        state = 1;
      } else if (ant2) {
        state = 2;
      } else if (ant3) {
        state = 3;
      }
    }
    currentLeverState = lever;
  } else {
    state = 0;
  }

  // Execute the current state function
  switch (state) {
    case 0:
      codeIdle(currentTime);
      break;
    case 1:
      codeIdleA(currentTime);
      break;
    case 2:
      codeIdleR(currentTime);
      break;
    case 3:
      codeIdleY(currentTime);
      break;
    case 4:
      codeActiveA(currentTime);
      break;
    case 5:
      codeActiveR(currentTime);
      break;
    case 6:
      codeActiveY(currentTime);
      break;
  }

  MEX.move(180, currentTime);
  NSA.move(180, currentTime);
  SSA.move(180, currentTime);
  EU.move(180, currentTime);
  SA.move(180, currentTime);
  SEA.move(180, currentTime);
  AUS.move(180, currentTime);
  FastLED.show();
  delay(10);
}