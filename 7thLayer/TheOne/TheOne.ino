#include <Arduino.h>
#include <FastLED.h>
#include <TaskScheduler.h>

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

Scheduler runner;

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

const int time = 500;
bool currentLeverState;

int currentState = 0;
static int state = 0;

// Task Functions
void codeReset() {
  if (state != currentState) {
    switch (state) {
      case 1:
        SSA.toggleMove(time);
        break;
      case 2:
        SSA.toggleMove(time);
        NSA.toggleMove(time);
        break;
      case 3:
        SEA.toggleMove(time);
        break;
      case 4:
        SSA.toggleMove(time);
        MEX.toggleMove(time);
        NSA.toggleMove(time);
        EU.toggleMove(time);
        SA.toggleMove(time);
        AUS.toggleMove(time);
        break;
      case 5:
        SSA.toggleMove(time);
        NSA.toggleMove(time);
        MEX.toggleMove(time);
        SEA.toggleMove(time);
        AUS.toggleMove(time);
        break;
      case 6:
        SEA.toggleMove(time);
        MEX.toggleMove(time);
        SA.toggleMove(time);
        AUS.toggleMove(time);
        break;
    }  
    Serial.println(state);
    currentState = state;
    crownReset();
  }
  delay(20);
}

void codeIdle() {
  codeReset();
  breathingHill();
}

void codeIdleA() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SSA.toggleMove(time);
  }
  breathingLever();
  delay(20);
}

void codeIdleR() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SSA.toggleMove(time);
    NSA.toggleMove(time);
  }
  breathingLever();
  delay(20);
}

void codeIdleY() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    SEA.toggleMove(time);
  }
  breathingLever();
  delay(20);
}

void codeActiveA() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(time);
    NSA.toggleMove(time);
    EU.toggleMove(time);
    SA.toggleMove(time);
    AUS.toggleMove(time);
  }
  displayAntA();
  delay(20);
}

void codeActiveR() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(time);
    SEA.toggleMove(time);
    AUS.toggleMove(time);
  }
  displayAntR();
  delay(20);
}

void codeActiveY() {
  if (state != currentState) {
    Serial.println(state);
    currentState = state;
    MEX.toggleMove(time);
    SA.toggleMove(time);
    AUS.toggleMove(time);
  }
  displayAntY();
  delay(20);
}

// Task Declarations
Task taskIdle(50, TASK_FOREVER, &codeIdle);
Task taskIdleA(50, TASK_FOREVER, &codeIdleA);
Task taskIdleR(50, TASK_FOREVER, &codeIdleR);
Task taskIdleY(50, TASK_FOREVER, &codeIdleY);
Task taskActiveA(50, TASK_FOREVER, &codeActiveA);
Task taskActiveR(50, TASK_FOREVER, &codeActiveR);
Task taskActiveY(50, TASK_FOREVER, &codeActiveY);

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
  long int time = millis();

  // Disable all tasks
  taskIdle.disable();
  taskIdleA.disable();
  taskIdleR.disable();
  taskIdleY.disable();
  taskActiveA.disable();
  taskActiveR.disable();
  taskActiveY.disable();

  bool lever = digitalRead(leverPin);
  bool ant1 = digitalRead(rfid1);
  bool ant2 = digitalRead(rfid2);
  bool ant3 = digitalRead(rfid3);

  // Serial.println(lever);

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

  // Enable the current task based on the state
  switch (state) {
    case 0:
      runner.addTask(taskIdle);
      taskIdle.enable();
      break;
    case 1:
      runner.addTask(taskIdleA);
      taskIdleA.enable();
      break;
    case 2:
      runner.addTask(taskIdleR);
      taskIdleR.enable();
      break;
    case 3:
      runner.addTask(taskIdleY);
      taskIdleY.enable();
      break;
    case 4:
      runner.addTask(taskActiveA);
      taskActiveA.enable();
      break;
    case 5:
      runner.addTask(taskActiveR);
      taskActiveR.enable();
      break;
    case 6:
      runner.addTask(taskActiveY);
      taskActiveY.enable();
      break;
  }
  MEX.move(180, time);
  NSA.move(180, time);
  SSA.move(180, time);
  EU.move(180, time);
  SA.move(180, time);
  SEA.move(180, time);
  AUS.move(180, time);
  runner.execute();  // Execute the scheduler
  FastLED.show();
  delay(10);
}
