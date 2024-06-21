#include <Arduino.h>
#include "ContinentSegment.h"

// Declare a Segment object globally
ContinentSegment MEX(14, 15);
ContinentSegment NSA(3, 2);
ContinentSegment SSA(5, 4);
ContinentSegment EU(7, 6);
ContinentSegment SA(9, 8);
ContinentSegment SEA(11, 10);
ContinentSegment AUS(13, 12);


void setup() {
  Serial.begin(9600);
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
}

void loop() {
  long int time = millis();
  if (Serial.available() > 0) {
    char received = Serial.read();
    Serial.print("Serial received: ");
    Serial.println(received);
    switch (received) {
      case '1':
        MEX.toggleMove(time);
        break;
      case '2':
        NSA.toggleMove(time);
        break;
      case '3':
        SSA.toggleMove(time);
        break;
      case '4':
        EU.toggleMove(time);
        break;
      case '5':
        SA.toggleMove(time);
        break;
      case '6':
        SEA.toggleMove(time);
        break;
      case '7':
        AUS.toggleMove(time);
        break;
      case 'A':
        raiseArgentineOrigin(time);
        raiseArgentineSpread(time);
        break;
      case 'R':
        raiseRedFireOrigin(time);
        raiseRedFireSpread(time);
        break;
      case 'Y':
        raiseYellowCrazyOrigin(time);
        raiseYellowCrazySpread(time);
        break;
      case 'T':
        MEX.toggleMove(time);
        NSA.toggleMove(time);
        SSA.toggleMove(time);
        EU.toggleMove(time);
        SA.toggleMove(time);
        SEA.toggleMove(time);
        AUS.toggleMove(time);
        break;
      default:
        break;
    }
  }
  MEX.move(180, time);
  NSA.move(180, time);
  SSA.move(180, time);
  EU.move(180, time);
  SA.move(180, time);
  SEA.move(180, time);
  AUS.move(180, time);

  delay(10);
}

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