#ifndef CONTINENTSEGMENT_H
#define CONTINENTSEGMENT_H

#include <Servo.h>

class ContinentSegment {
private:
  Servo servo;
  int servoPin;
  int switchPin;
  bool shouldMove;
  bool prevSwitchState;
  long int prevTime;

public:
  ContinentSegment(int initServoPin, int initSwitchPin);
  void begin();
  void toggleMove(long int time);
  void untoggleMove(int speed, long int time);
  void performMove(int speed);
  void stop(int speed, long int time, bool slowDown);
  void move(int speed, long int time);
};

#endif
