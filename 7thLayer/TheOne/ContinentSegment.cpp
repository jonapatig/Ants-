#include "ContinentSegment.h"
#include <Arduino.h>

ContinentSegment::ContinentSegment(int initServoPin, int initSwitchPin) {
  servoPin = initServoPin;
  switchPin = initSwitchPin;
  shouldMove = false;
  prevSwitchState = false;
  prevTime = 0;
}

void ContinentSegment::begin() {
  servo.attach(servoPin);
}

void ContinentSegment::toggleMove(long int time) {
  shouldMove = true;
  prevTime = time;
  // Serial.print("shouldMove toggled to: ");
  // Serial.println(shouldMove);
}

void ContinentSegment::untoggleMove(int speed, long int time) {
  if (shouldMove) {
    shouldMove = false;
    // Serial.print("shouldMove toggled to: ");
    // Serial.println(shouldMove);
    stop(speed, time, true);
  }
}

void ContinentSegment::performMove(int speed) {
  // Serial.print("performMove called. shouldMove: ");
  // Serial.println(shouldMove);
  if (shouldMove) {
    // Serial.println("Moving Servo");
    servo.write(speed);
  } else {
    // Serial.println("Servo Stopped");
  }
}

void ContinentSegment::stop(int speed, long int time, bool slowDown) {
  if (slowDown) {
    servo.write((-(speed - 90)) + 90);
    prevTime = time;
  } else if (prevTime + 25 <= time) {
    servo.write(90);
  }
}

void ContinentSegment::move(int speed, long int time) {
  bool switchState = digitalRead(switchPin);
  if (!switchState && prevSwitchState && prevTime + 45000 / speed <= time) {
    untoggleMove(speed, time);
  }
  prevSwitchState = switchState;
  stop(0, time, false);
  // Serial.println("Moving Servo to 180 (full speed in one direction)");
  performMove(speed);
}
