#ifndef CONVEYORBELTCONTROLLER_H
#define CONVEYORBELTCONTROLLER_H

#include <Servo.h>

class ConveyorBeltController {
public:
    ConveyorBeltController(int pin);
    void setup();
    void stop();
    void argentine();
    void redFire();
    void yellowCrazy();

private:
    Servo myServo;
    int servoPin;
};

#endif
