#ifndef MOTORPIDCONTROLLER_H
#define MOTORPIDCONTROLLER_H

#include <Arduino.h>
#include "RPMclass.h"

class MotorPIDController {
public:
    MotorPIDController(int pwmPin, int in1Pin, int in2Pin, int interruptPin);

    void setupMotor();
    void setRPM(float setpoint);
    void update();

private:
    int motorSpeedController(float RPMsetpoint, float measuredRPM);
    void setMotorDirection(int in1, int in2, bool direction);

    int motorApwm;
    int motorAin1;
    int motorAin2;
    int RPMcounterInterrupt;

    RPMclass RPMcounter;

    float RPMsetpoint;

    // PID params
    float Kbase;
    float Knormal;
    float Kp;
    float Ki;
    float Kd;

    float previousError;
    float integral;
    unsigned long lastTime;
};

#endif
