#include "MotorPIDController.h"

MotorPIDController::MotorPIDController(int pwmPin, int in1Pin, int in2Pin, int interruptPin)
  : motorApwm(pwmPin), motorAin1(in1Pin), motorAin2(in2Pin), RPMcounterInterrupt(interruptPin),
    RPMcounter(interruptPin), RPMsetpoint(0), Kbase(40), Knormal(1), Kp(0.1), Ki(0.001), Kd(-0.001),
    previousError(0), integral(0), lastTime(0) {}

void MotorPIDController::setupMotor() {
    pinMode(motorApwm, OUTPUT);
    pinMode(motorAin1, OUTPUT);
    pinMode(motorAin2, OUTPUT);

    // call change motor direction without specifying direction to turn on motor on init direction
    setMotorDirection(motorAin1, motorAin2, false);

    RPMcounter.setup();
}

void MotorPIDController::setRPM(float setpoint) {
    RPMsetpoint = setpoint;
}

void MotorPIDController::update() {
    RPMcounter.checkResetRPM();
    float measuredRPM = RPMcounter.getRPM();
    int controlSignal = motorSpeedController(RPMsetpoint, measuredRPM);
    analogWrite(motorApwm, controlSignal);

    Serial.print("Set RPM: ");
    Serial.print(RPMsetpoint);
    Serial.print(" , Control Signal: ");
    Serial.print(controlSignal);
    Serial.print(" , Measured RPM: ");
    Serial.println(measuredRPM);
}

int MotorPIDController::motorSpeedController(float RPMsetpoint, float measuredRPM) {
    unsigned long now = millis();
    float timeChange = (float)(now - lastTime);

    float error = RPMsetpoint - measuredRPM;
    integral += (error * timeChange);
    float derivative = (error - previousError) / timeChange;

    int controlValue = Kbase + Knormal * RPMsetpoint + Kp * error + Ki * integral + Kd * derivative;
    controlValue = constrain(controlValue, 0, 255);

    previousError = error;
    lastTime = now;

    return controlValue;
}

void MotorPIDController::setMotorDirection(int in1, int in2, bool direction) {
    digitalWrite(in1, direction);
    digitalWrite(in2, !direction);
}
