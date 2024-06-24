#include "RFIDReader.h"

RFIDReader::RFIDReader(int pin1, int pin2, int pin3)
  : _pin1(pin1), _pin2(pin2), _pin3(pin3) {}

void RFIDReader::begin() {
    pinMode(_pin1, INPUT);
    pinMode(_pin2, INPUT);
    pinMode(_pin3, INPUT);
}

int RFIDReader::readRFID() {
    if(digitalRead(_pin1)) {
        return 1;
    }
    if(digitalRead(_pin2)) {
        return 2;
    }
    if(digitalRead(_pin3)) {
        return 3;
    }
    return 0;
}
