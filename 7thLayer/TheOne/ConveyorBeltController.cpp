#include "ConveyorBeltController.h"

ConveyorBeltController::ConveyorBeltController(int pin) : servoPin(pin) {}

void ConveyorBeltController::setup() {
    myServo.attach(servoPin);
}

void ConveyorBeltController::stop() {
    myServo.write(90); // off
}

void ConveyorBeltController::argentine() {
    myServo.write(120); // min speed
}

void ConveyorBeltController::redFire() {
    myServo.write(180); // max speed
}

void ConveyorBeltController::yellowCrazy() {
    myServo.write(160); // change speed calculated the data mapping
}
