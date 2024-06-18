/// @file    RPM.cpp
/// @brief   Implementation of the RPM class

#include "RPM.h"

RPM::RPM(int interruptPin) 
    : interruptPin(interruptPin) {
    RPM = 0;
    previousInterupt =0;
}

void RPM::setup() {
  delay(2000);// whatever is safe or somethin
  attachInterrupt(digitalPinToInterrupt(interruptPin), countRPM, FALLING);  // Attach the interrupt
}

void RPM::checkResetRPM(){
  int currentTime = millis();
  if(currentTime - previousInterupt > 60000){
    RPM = 0;
  }
}

void RPM::countRPM() {
  int interupt = millis();
  delayMicroseconds(50);          //delay 50 microseconds to prevent accidental triggers
  if(digitalRead(interruptPin)){  //if pin still high stop function
    return ; 
  }
  measuredRPM = (interupt-previousInterupt)/60000; // 60000 is one minute 
  RPM = (RPM + measuredRPM)/2; //this is a little lerp filter
  previousInterupt = interupt;
}

void RPM::getRPM(){
  return RPM;
}

