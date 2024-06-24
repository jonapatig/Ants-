#include "RFIDclass.h"
#include <Arduino.h>
#define SS_PIN 49
#define RST_PIN 48

RFIDclass rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  ; // Wait for serial port to connect. Needed for native USB
}
  rfid.setup();
}

void loop() {
  rfid.main();
}
