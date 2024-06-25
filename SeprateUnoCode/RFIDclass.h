#ifndef RFIDCLASS_H
#define RFIDCLASS_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDclass {
public:
    RFIDclass(int SS_PIN, int RST_PIN, int card1Pin, int card2Pin, int card3Pin);
    void setup();
    void main();  //

private:
    bool compareUIDs(byte *uid1, byte *uid2, byte size);
    bool cardPresent;  // Track the state of card presence
    unsigned long lastDetectedTime;
    unsigned long debounceDelay;
    MFRC522 mfrc522;  // Declare the mfrc522 member

    int getCardNumber();  // Function to get card number

    // Add pin members
    int card1Pin;
    int card2Pin;
    int card3Pin;
};

#endif // RFIDCLASS_H
