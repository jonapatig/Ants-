#ifndef MANDIBLE_LEVER_H
#define MANDIBLE_LEVER_H

#include <Arduino.h>

class MandibleLever {
public:
    MandibleLever(uint8_t inputPin, uint8_t outputPin, unsigned long debounceDelay = 50);
    void begin();
    void update();

private:
    uint8_t _inputPin;
    uint8_t _outputPin;
    unsigned long _debounceDelay;
    int _leverState;
    int _lastLeverState;
    unsigned long _lastDebounceTime;
};

#endif
