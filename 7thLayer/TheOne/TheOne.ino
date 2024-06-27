//This code was a work of love from the entirety of the Ant Invasion team.  Though code was directly contributed by Oskar, Willem, Jona, and Chris, input and guidence was provided by the whole team!

#include <Arduino.h>
#include <FastLED.h>

#include "AntSelect.h"
#include "CrownLeds.h"
#include "EcoHalo.h"
#include "EcoBranch.h"
#include "ContinentSegment.h"
#include "ConveyorBeltController.h"

const int leverPin = 22;  // Lever
const int rfid1 = 23;     // Ant A
const int rfid2 = 25;     // Ant Y
const int rfid3 = 24;     // Ant R

// Declare a Segment object globally
ContinentSegment MEX(14, 15);
ContinentSegment NSA(3, 2);
ContinentSegment SSA(5, 4);
ContinentSegment EU(7, 6);
ContinentSegment SA(9, 8);
ContinentSegment SEA(11, 10);
ContinentSegment AUS(13, 12);

// Track segment positions (true for up, false for down)
bool MEX_up = false;
bool NSA_up = false;
bool SSA_up = false;
bool EU_up = false;
bool SA_up = false;
bool SEA_up = false;
bool AUS_up = false;

// Function declarations
void breathingLever();
void breathingHill();
void hillActive();
void displayAntA();
void displayAntR();
void displayAntY();
void crownReset();
void fullEco();
void damagedEco1();
void damagedEco2();
void fullEcoBranch();
void damagedEcoBranch1();
void damagedEcoBranch2();
void leverForward();
void leverBackward();

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
ConveyorBeltController conveyor(DATA_PIN_CONVEYOR);

CRGB ledsAnts[NUM_LEDS_ANTS];
CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsCrown[NUM_LEDS_CROWN];
CRGB ledsBranch[NUM_LEDS_BRANCH];

bool currentLeverState;
bool state0Activated = false;
bool state123Activated = false;

int prevState = 0;
int state = 0;

void toggleSegment(ContinentSegment &segment, bool &upState, long int time) {
  segment.toggleMove(time);
  upState = !upState;
}

void lowerSegment(ContinentSegment &segment, bool &upState, long int time) {
  if (upState) {
    segment.toggleMove(time);
    upState = false;
  }
}

void raiseArgentineOrigin(long int time) {
  toggleSegment(SSA, SSA_up, time);
}

void raiseArgentineSpread(long int time) {
  toggleSegment(MEX, MEX_up, time);
  toggleSegment(NSA, NSA_up, time);
  toggleSegment(EU, EU_up, time);
  toggleSegment(SA, SA_up, time);
  toggleSegment(AUS, AUS_up, time);
}

void raiseRedFireOrigin(long int time) {
  toggleSegment(NSA, NSA_up, time);
  toggleSegment(SSA, SSA_up, time);
}

void raiseRedFireSpread(long int time) {
  toggleSegment(MEX, MEX_up, time);
  toggleSegment(SEA, SEA_up, time);
  toggleSegment(AUS, AUS_up, time);
}

void raiseYellowCrazyOrigin(long int time) {
  toggleSegment(SEA, SEA_up, time);
}

void raiseYellowCrazySpread(long int time) {
  toggleSegment(MEX, MEX_up, time);
  toggleSegment(SA, SA_up, time);
  toggleSegment(AUS, AUS_up, time);
}

// Task Functions
void codeReset(uint32_t currentTime) {
  if (state != prevState) {
    conveyor.stop();
    // Lower all segments that are currently up
    lowerSegment(MEX, MEX_up, currentTime);
    lowerSegment(NSA, NSA_up, currentTime);
    lowerSegment(SSA, SSA_up, currentTime);
    lowerSegment(EU, EU_up, currentTime);
    lowerSegment(SA, SA_up, currentTime);
    lowerSegment(SEA, SEA_up, currentTime);
    lowerSegment(AUS, AUS_up, currentTime);

    state0Activated = false;
    state123Activated = false;
  }
  delay(10);
}

void codeIdle(uint32_t currentTime) {
  codeReset(currentTime);
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
  }
  crownReset();
  fullEco();
  fullEcoBranch();
  breathingHill();
}

void codeIdleA(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseArgentineOrigin(currentTime);
  }
  fullEco();
  fullEcoBranch();
  breathingLever();
  delay(1);
}

void codeIdleR(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseRedFireOrigin(currentTime);
  }
  fullEco();
  fullEcoBranch();
  breathingLever();
  delay(1);
}

void codeIdleY(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseYellowCrazyOrigin(currentTime);
  }
  fullEco();
  fullEcoBranch();
  breathingLever();
  delay(1);
}

// Timings for the system
uint32_t startTime = 0;
int invasionTransition = 10000;
int ecoTransition = invasionTransition + 5000;
int moneyTransition = ecoTransition + 5000;
uint32_t endTransition = moneyTransition + 8000;
uint32_t resetDone = endTransition + 5000;
bool state7Printed = false;
bool state8Printed = false;

void codeActiveA(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseArgentineSpread(currentTime);
    startTime = currentTime;
    state7Printed = false;
    state8Printed = false;
  } else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      fullEco();
      fullEcoBranch();
    } else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco2();
      damagedEcoBranch2();
    } else if (moneyTransition + startTime <= currentTime){
      if (!state7Printed) {
        Serial.println("7");
        state7Printed = true;
      }
      if (moneyTransition + startTime + 2000 <= currentTime){
        damagedEco2();
        damagedEcoBranch2();
        displayAntA();
        conveyor.argentine();
      }
    }
  }
  hillActive();
  delay(1);
}

void codeActiveR(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseRedFireSpread(currentTime);
    startTime = currentTime;
    state7Printed = false;
    state8Printed = false;
  } else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      fullEco();
      fullEcoBranch();
    } else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco1();
      damagedEcoBranch1();
    } else if (moneyTransition + startTime <= currentTime){
      if (!state7Printed) {
        Serial.println("7");
        state7Printed = true;
      }
      if (moneyTransition + startTime + 2000 <= currentTime){
        damagedEco1();
        damagedEcoBranch1();
        conveyor.redFire();
        displayAntR();
      }

    }
  }
  hillActive();
  delay(1);
}

void codeActiveY(uint32_t currentTime) {
  if (state != prevState) {
    Serial.println(state);
    prevState = state;
    raiseYellowCrazySpread(currentTime);
    startTime = currentTime;
    state7Printed = false;
    state8Printed = false;
  } else {
    if ((invasionTransition + startTime <= currentTime) && (currentTime <= ecoTransition + startTime)) {
      fullEco();
      fullEcoBranch();
    } else if ((ecoTransition + startTime <= currentTime) && (currentTime <= moneyTransition + startTime)) {
      damagedEco2();
      damagedEcoBranch2();
    } else if (moneyTransition + startTime <= currentTime){
      if (!state7Printed) {
        Serial.println("7");
        state7Printed = true;
      }
      if (moneyTransition + startTime + 2000 <= currentTime){
        damagedEco2();
        damagedEcoBranch2();
        conveyor.yellowCrazy();
        displayAntY();
      }

    }
  }
  hillActive();
  delay(1);
}

void setup() {
  Serial.begin(9600);
  currentLeverState = !digitalRead(leverPin);
  conveyor.setup();
  Serial.println("0");
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
  FastLED.addLeds<WS2811, DATA_PIN_BRANCH, BRG>(ledsBranch, NUM_LEDS_BRANCH);
  FastLED.setBrightness(50);

  delay(500);
}

void loop() {
  static uint32_t lastStateChangeTime = 0;
  uint32_t currentTime = millis();

  bool lever = digitalRead(leverPin);
  bool ant1 = digitalRead(rfid1);
  bool ant2 = digitalRead(rfid2);
  bool ant3 = digitalRead(rfid3);

  // Serial.print("Lever: ");
  // Serial.print(lever);
  // Serial.print(", Ant1: ");
  // Serial.print(ant1);
  // Serial.print(", Ant2: ");
  // Serial.print(ant2);
  // Serial.print(", Ant3: ");
  // Serial.println(ant3);

  if (currentTime - lastStateChangeTime >= 5000) {
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
      lastStateChangeTime = currentTime;
    } else {
      state = 0;
      state0Activated = true;
      lastStateChangeTime = currentTime;
    }
  }

  // Execute the current state function
  switch (state) {
    case 0:
      codeIdle(currentTime);
      break;
    case 1:
      codeIdleA(currentTime);
      if (lever==currentLeverState){
        if(lever){
          leverBackward();
        }
        else{
          leverForward();
        }
      }
      break;
    case 2:
      codeIdleR(currentTime);
      if (lever==currentLeverState){
        if(lever){
          leverBackward();
        }
        else{
          leverForward();
        }
      }
      break;
    case 3:
      codeIdleY(currentTime);
      if (lever==currentLeverState){
        if(lever){
          leverBackward();
        }
        else{
          leverForward();
        }
      }
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
