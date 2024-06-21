/// @file    RPMclass.cpp
/// @brief   Implementation of the RPM class

#include "RPMclass.h"
#include <Arduino.h>

// Initialize static member
RPMclass* RPMclass::instance = nullptr;
volatile bool RPMclass::interruptFlag = false;  // Initialize the interrupt flag

RPMclass::RPMclass(int interruptPin) 
    : interruptPin(interruptPin), previousInterrupt(0), RPM(0) {
    instance = this;  // Assign current instance to static member
}

void RPMclass::setup() {
    delay(2000); // whatever is safe or something
    attachInterrupt(digitalPinToInterrupt(interruptPin), RPMclass::countRPM, CHANGE);  // Attach the interrupt
}

void RPMclass::checkResetRPM(){
    long currentTime = millis();
    if(currentTime - previousInterrupt > 1000){  // Corrected typo
        RPM = 0;
    }
}

void RPMclass::countRPM() {
    if (instance != nullptr) {
        long interruptTime = millis();
        if (interruptTime - instance->previousInterrupt < 50) {
            // Ignore interrupts that occur within 50ms to debounce
            return;
        }
        // 60000 is one minute, there are two triggers on one rotation so divide by two makes 30000
        float measuredRPM = 15000 / (interruptTime - instance->previousInterrupt);

        instance->RPM = (instance->RPM +0.5* measuredRPM)/1.5; // change this to add filters and such
        instance->previousInterrupt = interruptTime;
        interruptFlag = true;  // Set the interrupt flag
    }
}

float RPMclass::getRPM() {  // Change return type to float
    return RPM;
}

bool RPMclass::getInterruptFlag() {
    bool flag = interruptFlag;
    interruptFlag = false;  // Reset the flag after reading
    return flag;
}
