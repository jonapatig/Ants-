#include "MandibleLever.h"

MandibleLever::MandibleLever(uint8_t inputPin, uint8_t outputPin, unsigned long debounceDelay)
    : _inputPin(inputPin), _outputPin(outputPin), _debounceDelay(debounceDelay), _leverState(HIGH), _lastLeverState(HIGH), _lastDebounceTime(0) {
}

void MandibleLever::begin() {
    pinMode(_inputPin, INPUT_PULLUP);
    pinMode(_outputPin, OUTPUT);
    _leverState = digitalRead(_inputPin);
}

void MandibleLever::update() {
    int currentReading = digitalRead(_inputPin);

    if (currentReading != _lastLeverState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (currentReading != _leverState) {
            _leverState = currentReading;
            digitalWrite(_outputPin, !_leverState);
        }
    }

    _lastLeverState = currentReading;
}
