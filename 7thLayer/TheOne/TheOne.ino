#include <Arduino.h>
#include <FastLED.h>
#include <TaskScheduler.h>

#include "AntSelect.h"
#include "CrownLeds.h"
#include "RFIDclass.h"
#include "ContinentSegment.h"

const int SS_PIN = 48;
const int RST_PIN = 49;

RFIDclass rfid(SS_PIN, RST_PIN);

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
const int DATA_PIN_ANTS = 47;

const int NUM_LEDS_HALO = 96;
const int DATA_PIN_HALO = 45;

const int NUM_LEDS_CROWN = 160;
const int DATA_PIN_CROWN = 44;

const int time = 500;

CRGB ledsAnts[NUM_LEDS_ANTS];
CRGB ledsHalo[NUM_LEDS_HALO];
CRGB ledsCrown[NUM_LEDS_CROWN];

// Task Functions
void codeIdle() {
  breathingHill();
}

void codeIdleA() {
  SSA.toggleMove(time);
  breathingLever();
  displayAntA();
}

void codeIdleR() {
  NSA.toggleMove(time);
  SSA.toggleMove(time);
}
void codeShowIdleR() {
  displayAntR();
}

void codeIdleY() {
  SEA.toggleMove(time);
  breathingLever();
}

void codeActiveA() {
  MEX.toggleMove(time);
  NSA.toggleMove(time);
  EU.toggleMove(time);
  SA.toggleMove(time);
  AUS.toggleMove(time);
  displayAntA();
}

void codeActiveR() {
  MEX.toggleMove(time);
  SEA.toggleMove(time);
  AUS.toggleMove(time);
  displayAntR();
}

void codeActiveY() {
  MEX.toggleMove(time);
  SA.toggleMove(time);
  AUS.toggleMove(time);
  displayAntY();
}

void codeReset() {
  crownReset();
}

// Task Declarations
Task taskIdle(50, TASK_FOREVER, &codeIdle);
Task taskIdleA(50, TASK_FOREVER, &codeIdleA);
Task taskIdleR(50, TASK_FOREVER, &codeIdleR);
Task taskIdleY(50, TASK_FOREVER, &codeIdleY);
Task taskActiveA(50, TASK_FOREVER, &codeActiveA);
Task taskActiveR(50, TASK_FOREVER, &codeActiveR);
Task taskActiveY(50, TASK_FOREVER, &codeActiveY);
Task taskReset(50, TASK_FOREVER, &codeReset);
Task showIdleR(50,TASK_FOREVER, &codeShowIdleR);

void setup() {
  Serial.begin(9600);
  // while (!Serial) {
  //   ; // Wait for serial port to connect. Needed for native USB
  // }
  Serial.println("Setup Initialized");

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

  FastLED.addLeds<WS2812B, DATA_PIN_ANTS, GRB>(ledsAnts, NUM_LEDS_ANTS);
  FastLED.addLeds<WS2812B, DATA_PIN_HALO, GRB>(ledsHalo, NUM_LEDS_HALO);
  FastLED.addLeds<WS2812B, DATA_PIN_CROWN, GRB>(ledsCrown, NUM_LEDS_CROWN);
  FastLED.setBrightness(50);
  rfid.setup();
  delay(500);
}

void loop() {
  static uint32_t lastSwitchTime = 0;
  uint32_t currentTime = millis();
  static int state = 0;

  // Disable all tasks
  taskIdle.disable();
  taskIdleA.disable();
  taskIdleR.disable();
  taskIdleY.disable();
  taskActiveA.disable();
  taskActiveR.disable();
  taskActiveY.disable();
  taskReset.disable();

  int rfidState = rfid.main();
  // int rfidState = 1;
  Serial.print("RFID State: ");
  Serial.println(rfidState);

  switch (rfidState) {
    case 0:
      state = 0;
      break;
    case 1:
      state = 4;
      break;
    case 2:
      state = 5;
      break;
    case 3:
      state = 6;
      break;
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
      runner.addTask(showIdleR);
      showIdleR.enable();
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
    case 7:
      runner.addTask(taskReset);
      taskReset.enable();
      break;
  }

  runner.execute();  // Execute the scheduler
  FastLED.show();
  delay(20);
}
