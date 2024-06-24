#include <ConveyorBeltController.h>

ConveyorBeltController conveyor(9); // initialize with pin number

void setup() {
    conveyor.setup();
}

void loop() {
    // Example usage
    conveyor.stop();
    delay(1000); // wait for a second
    conveyor.argentine();
    delay(1000); // wait for a second
    conveyor.redFire();
    delay(1000); // wait for a second
    conveyor.yellowCrazy(); 
    delay(1000); // wait for a second
}
