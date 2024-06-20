#include <RFIDclass.h>

#define SS_PIN 10
#define RST_PIN 5

RFIDclass rfid(SS_PIN, RST_PIN);

void setup() {
    rfid.setup();
}

void loop() {
    rfid.main();
}
