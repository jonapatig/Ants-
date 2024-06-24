/// @file    RFIDclass.h
/// @brief   Class for the usage of RFID reader

#ifndef RFIDCLASS_H
#define RFIDCLASS_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDclass {
public:
    RFIDclass(int SS_PIN, int RST_PIN);
    void setup();
    int main();  // Change to return int

private:
    void printCardNumber();
    bool compareUIDs(byte *uid1, byte *uid2, byte size);
    bool cardPresent;  // Track the state of card presence
    unsigned long lastDetectedTime;
    unsigned long debounceDelay;
    MFRC522 mfrc522;  // Declare the mfrc522 member

    int getCardNumber();  // New function to get card number
};

#endif // RFIDCLASS_H
