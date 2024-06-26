#include <Arduino.h>
#include <FastLED.h>

#include "AntSelect.h"
#include "CrownLeds.h"
#include "EcoHalo.h"
#include "Branch.h"
#include "ContinentSegment.h"

const int leverPin = 22;  // Lever
const int rfid1 = 23;     // Ant A
const int rfid2 = 24;     // Ant Y
const int rfid3 = 25;     // Ant R

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
void runBranch();
void branch1();
void branch2();
void fullEco();
void damagedEco1();
void damagedEco2();


// LED Definitions
const int NUM_LEDS_ANTS = 180;
const int DATA_PIN_ANTS = 18;

const int NUM_LEDS_HALO = 96;
const int DATA_PIN_HALO = 19;

const int NUM_LEDS_CROWN = 160;
const int DATA_PIN_CROWN = 20;

const int NUM_LEDS_BRANCH = 22;
const int DATA_PIN_BRANCH = 21;

// Conveyor Pin
const int DATA_PIN_CONVEYOR = 17;

CRGB ledsAnts[NUM_LEDS_ANTS];
CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsCrown[NUM_LEDS_CROWN];
CRGB ledsBranch[NUM_LEDS_BRANCH];

bool currentLeverState;
bool state0Activated = false;
bool state123Activated = false;

int prevState = 0;
int state = 0;

void raiseArgentineOrigin(long int time) {
  SSA.toggleMove(time);
  Serial.println("Raising Argentine Origin");
}

void raiseArgentineSpread(long int time) {
  MEX.toggleMove(time);
  NSA.toggleMove(time);
  EU.toggleMove(time);
  SA.toggleMove(time);
  AUS.toggleMove(time);
  Serial.println("Raising Argentine Spread");
}

void raiseRedFireOrigin(long int time) {
  NSA.toggleMove(time);
  SSA.toggleMove(time);
  Serial.println("Raising Argentine Origin");
}

void raiseRedFireSpread(long int time) {
  MEX.toggleMove(time);
  SEA.toggleMove(time);
  AUS.toggleMove(time);
  Serial.println("Raising Argentine Spread");
}

void raiseYellowCrazyOrigin(long int time) {
  SEA.toggleMove(time);
  Serial.println("Raising Argentine Origin");
}

void raiseYellowCrazySpread(long int time) {
  MEX.toggleMove(time);
  SA.toggleMove(time);
  AUS.toggleMove(time);
  Serial.println("Raising Argentine Spread");
}

// Task Functions
void codeReset(uint32_t currentTime) {
  if (state != prevState) {
    switch (prevState) {
      case 1:
        raiseArgentineOrigin(currentTime);
        break;
      case 2:
        raiseRedFireOrigin(currentTime);
        break;
      case 3:
        raiseYellowCrazyOrigin(currentTime);
        break;
      case 4:
        raiseArgentineOrigin(currentTime);
        raiseArgentineSpread(currentTime);
        break;
      case 5:
        raiseRedFireOrigin(currentTime);
        raiseRedFireSpread(currentTime);
        break;
      case 6:
        raiseYellowCrazyOrigin(currentTime);
        raiseYellowCrazySpread(currentTime);
        break;
    }
    state0Activated = false;
    state123Activated = false;
  }
  delay(1);
}

void codeIdle(uint32_t currentTime) {
  codeReset(currentTime);
  prevState = state;
  crownReset();
  runBranch();
  fullEco();
  breathingHill();
}

void codeIdleA(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseArgentineOrigin(currentTime);
  }
  breathingLever();
  delay(1);
}

void codeIdleR(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseRedFireOrigin(currentTime);
  }
  breathingLever();
  delay(1);
}

void codeIdleY(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseYellowCrazyOrigin(currentTime);
  }
  breathingHill();
  delay(1);
}

// Timings for the system
uint32_t startTime = 0;
int invasionTransition = 5000;
int ecoTransition = invasionTransition + 5000;
int moneyTransition = ecoTransition + 5000;
int endTransition = moneyTransition+ 5000;

void codeActiveA(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseArgentineSpread(currentTime);
    startTime = currentTime;
  }
  else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      runBranch();
      fullEco();
    }
    else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco2();
    }
    else if ((moneyTransition + startTime <= currentTime) && (currentTime <= endTransition + startTime)) {
      displayAntA();
    }
    else {
      // Add any code here if needed for states not covered above
    }
  }
  delay(1);
}

void codeActiveR(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseRedFireSpread(currentTime);
    startTime = currentTime;
  }
  else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      runBranch();
      fullEco();
      Serial.println("Invasion");
    }
    else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco2();
      Serial.println("EcoDamage");
    }
    else if ((moneyTransition + startTime <= currentTime) && (currentTime <= endTransition + startTime)) {
      displayAntR();
      Serial.println("MoneyDamage");
    }
    else if (endTransition + startTime < currentTime){
      Serial.println("End");
    }
  }
  delay(1);
}

void codeActiveY(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseYellowCrazySpread(currentTime);
    startTime = currentTime;
  }
  else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      runBranch();
      fullEco();
    }
    else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco1();
    }
    else if ((moneyTransition + startTime <= currentTime) && (currentTime <= endTransition + startTime)) {
      displayAntY();
    }
    else {
      // Add any code here if needed for states not covered above
    }
  }
  delay(1);
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

  if (ant1 || ant2 || ant3) {
    if (lever != currentLeverState) {
      if (state123Activated) {
        if (ant1) {
          state = 4;
        } else if (ant2) {
          state = 5;
        } else if (ant3) {
          state = 6;
        }
      }
    } else {
      if (state0Activated) {
        if (ant1) {
          state = 1;
        } else if (ant2) {
          state = 2;
        } else if (ant3) {
          state = 3;
        }
        state123Activated = true;
      }
    }
    currentLeverState = lever;
    state0Activated = false;
  } else {
    state = 0;
    state0Activated = true;
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

  MEX.move(100, currentTime);
  NSA.move(100, currentTime);
  SSA.move(100, currentTime);
  EU.move(100, currentTime);
  SA.move(100, currentTime);
  SEA.move(100, currentTime);
  AUS.move(100, currentTime);
  FastLED.show();
  delay(10);
}
