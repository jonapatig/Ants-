// file to test RPMclass
#include "RPMclass.h"

const int interruptPin = 2;  // Pin 2 is used for the interrupt (depends on the board)

RPMclass RPMcounter(interruptPin);

void setup() {
    Serial.begin(9600);
    RPMcounter.setup();  // Initialize the RPM counter
}

void loop() {
    if (RPMcounter.getInterruptFlag()) {
        Serial.print("RPM: ");
        Serial.println(RPMcounter.getRPM());
    }
    
    RPMcounter.checkResetRPM();
    delay(50);
}
