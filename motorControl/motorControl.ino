#include <Arduino.h>
#include "MotorPIDController.h"

#define motorApwm 6
#define motorAin1 5
#define motorAin2 4
int RPMcounterInterrupt = 2;

MotorPIDController motorController(motorApwm, motorAin1, motorAin2, RPMcounterInterrupt);

void setup() {
    Serial.begin(9600);
    motorController.setupMotor();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');  // Read serial input until newline character
        float setRPM = input.toInt();  // Convert the input string to an integer
        motorController.setRPM(setRPM);
    }

    motorController.update();
    delay(10);
}
