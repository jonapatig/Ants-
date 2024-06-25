#include "MandibleLever.h"
#include <SPI.h>
#include "RFIDclass.h"

// Define pins for the RFID reader
#define SS_PIN 10
#define RST_PIN 5

// Define pins for the LEDs (or other outputs)
#define CARD1_PIN 2
#define CARD2_PIN 3
#define CARD3_PIN 4

// Create an instance of the RFIDclass
RFIDclass rfid(SS_PIN, RST_PIN, CARD1_PIN, CARD2_PIN, CARD3_PIN);

#define leverInput 8
#define leverOutput 9

MandibleLever lever(leverInput, leverOutput);

void setup() {
    Serial.begin(9600);
    lever.begin();
    // Initialize the RFID reader
    rfid.setup();
}

void loop() {
    lever.update();
    // Call the main function of the RFIDclass
    rfid.main();
    
    // Optional: Add a small delay to avoid flooding the serial output (for debugging)
    delay(10);
}
