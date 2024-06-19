/// @file    RPMclass.cpp
/// @brief   Implementation of the RPM class

#include "RPMclass.h"
#include <Arduino.h>

RPMclass::RPMclass(int interruptPin) 
    : interruptPin(interruptPin), previousInterrupt(0), RPM(0) {  // Initialize RPM and previousInterrupt in initializer list
}

void RPMclass::setup() {
    delay(2000); // whatever is safe or something
    attachInterrupt(digitalPinToInterrupt(interruptPin), countRPM, FALLING);  // Attach the interrupt
}

void RPMclass::checkResetRPM(){
    long currentTime = millis();
    if(currentTime - previousInterrupt > 60000){  // Corrected typo
        RPM = 0;
    }
}

void RPMclass::countRPM() {
    long interruptTime = millis();
    if (interruptTime - previousInterrupt < 50) {
        // Ignore interrupts that occur within 50ms to debounce
        return;
    }
    // 60000 is one minute, there are two triggers on one rotation so divide by two makes 30000
    float measuredRPM = 30000.0 / (interruptTime - previousInterrupt);

    RPM = measuredRPM; // change this to add filters and such
    previousInterrupt = interruptTime;
}

float RPMclass::getRPM() {  // Change return type to float
    return RPM;
}
