#include <RFIDReader.h>

// Define the pins
#define PIN1 1
#define PIN2 2
#define PIN3 3

RFIDReader rfidReader(PIN1, PIN2, PIN3);

void setup() {
  Serial.begin(9600);
  rfidReader.begin();
}

void loop() {
  int id = rfidReader.readRFID();
  if (id != 0) {
    Serial.print("RFID Tag Read: ");
    Serial.println(id);
  }
  delay(500);
}
