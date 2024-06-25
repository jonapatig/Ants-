#include "RFIDclass.h"

RFIDclass::RFIDclass(int SS_PIN, int RST_PIN, int card1Pin, int card2Pin, int card3Pin)
    : mfrc522(SS_PIN, RST_PIN), cardPresent(false), lastDetectedTime(0), debounceDelay(200),
      card1Pin(card1Pin), card2Pin(card2Pin), card3Pin(card3Pin) {}

void RFIDclass::setup() {
    SPI.begin();           // Initialize SPI bus
    mfrc522.PCD_Init();    // Initialize MFRC522
    pinMode(card1Pin, OUTPUT);
    pinMode(card2Pin, OUTPUT);
    pinMode(card3Pin, OUTPUT);
    digitalWrite(card1Pin, LOW);
    digitalWrite(card2Pin, LOW);
    digitalWrite(card3Pin, LOW);
}

void RFIDclass::main() {
    bool cardDetected = mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();

    if (cardDetected) {
        // If a card is detected, check how long it has been present
        lastDetectedTime = millis(); // Update the last detected time
            // Card is detected and has been present for longer than debounceDelay
        if (!cardPresent) {
            cardPresent = true; // Set the card present flag

            int cardNumber = getCardNumber();
            Serial.println(cardNumber);
            digitalWrite(card1Pin, cardNumber == 1 ? HIGH : LOW);
            digitalWrite(card2Pin, cardNumber == 2 ? HIGH : LOW);
            digitalWrite(card3Pin, cardNumber == 3 ? HIGH : LOW);
            
            
        }
    } else {
        // No card detected
        if (cardPresent && millis() - lastDetectedTime > debounceDelay) {
            // Card was previously detected but is now absent for longer than debounceDelay
            cardPresent = false;
            digitalWrite(card1Pin, LOW);
            digitalWrite(card2Pin, LOW);
            digitalWrite(card3Pin, LOW);
        }
    }
}

int RFIDclass::getCardNumber() {
    byte card1UID[] = {0x04, 0x53, 0x63, 0x62, 0xEC, 0x6B, 0x80};  
    byte card2UID[] = {0x04, 0x56, 0x64, 0x62, 0xEC, 0x6B, 0x80};
    byte card3UID[] = {0x04, 0x4C, 0x64, 0x62, 0xEC, 0x6B, 0x80};

    if (compareUIDs(mfrc522.uid.uidByte, card1UID, mfrc522.uid.size)) {
        return 1;
    } else if (compareUIDs(mfrc522.uid.uidByte, card2UID, mfrc522.uid.size)) {
        return 2;
    } else if (compareUIDs(mfrc522.uid.uidByte, card3UID, mfrc522.uid.size)) {
        return 3;
    } else {
        return 0;
    }
}

bool RFIDclass::compareUIDs(byte *uid1, byte *uid2, byte size) {
    for (byte i = 0; i < size; i++) {
        if (uid1[i] != uid2[i]) {
            return false;
        }
    }
    return true;
}
