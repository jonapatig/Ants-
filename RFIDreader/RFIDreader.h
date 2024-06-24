#ifndef RFIDREADER_H
#define RFIDREADER_H

#include "Arduino.h"

class RFIDReader {
public:
    RFIDReader(int pin1, int pin2, int pin3);
    void begin();
    int readRFID();

private:
    int _pin1, _pin2, _pin3;
};

#endif
