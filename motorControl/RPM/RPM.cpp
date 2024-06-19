/// @file    RPM.cpp
/// @brief   Implementation of the RPM class

#include "RPM.h"

RPM::RPM(int interruptPin) 
    : interruptPin(interruptPin), previousInterrupt(0), RPM(0) {  // Initialize RPM and previousInterrupt in initializer list
}

void RPM::setup() {
  delay(2000);// whatever is safe or somethin
  attachInterrupt(digitalPinToInterrupt(interruptPin), countRPM, FALLING);  // Attach the interrupt
}

void RPM::checkResetRPM(){
  long currentTime = millis();
  if(currentTime - previousInterupt > 60000){
    RPM = 0;
  }
}

void RPM::countRPM() {
  long interruptTime = millis();
  if (interruptTime - previousInterrupt < 50) {
    // Ignore interrupts that occur within 50ms to debounce
    return;
  }
  //60000 is one minute, there are two triggers on one rotation so divede by to makes 30000
  float measuredRPM = 30000.0 / (interruptTime - previousInterrupt);

  RPM = measuredRPM; // change this to add filters and such
  previousInterrupt = interruptTime;
}

float RPM::getRPM(){
  return RPM;
}

