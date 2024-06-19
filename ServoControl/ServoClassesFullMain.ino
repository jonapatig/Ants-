#include <Arduino.h>
#include "ContinentSegment.h"

// Declare a Segment object globally
ContinentSegment Europe(6, 4);
ContinentSegment SouthAmerica(7, 3);


long int timer;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup Initialized");
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Europe.begin();
  SouthAmerica.begin();
  timer = 0;
}

void loop() {
  if (Serial.available() > 0) {
    char received = Serial.read();
    Serial.print("Serial received: ");
    Serial.println(received);
    if (received == 'O') {
      raiseArgentineOrigin();
    } else if (received == 'S') {
      raiseArgentineSpread();
    }
  }
  long int time = millis();
  Europe.move(180, time);
  SouthAmerica.move(180, time);
  delay(10);

  if (timer + 1000 <= time) {
    Serial.println("now");
    timer = time;
    raiseArgentineOrigin();
  }
}

void raiseArgentineOrigin() {
  SouthAmerica.toggleMove(millis());
  Serial.println("Raising Origin");
}

void raiseArgentineSpread() {
  Europe.toggleMove(millis());
  Serial.println("Raising Spread");
}