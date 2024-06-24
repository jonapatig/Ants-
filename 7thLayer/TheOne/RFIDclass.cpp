#include "RFIDclass.h"

RFIDclass::RFIDclass(int SS_PIN, int RST_PIN)
    : mfrc522(SS_PIN, RST_PIN), cardPresent(false), lastDetectedTime(0), debounceDelay(50) {}

void RFIDclass::setup() {
    SPI.begin();           // Initialize SPI bus
    mfrc522.PCD_Init();    // Initialize MFRC522
}

int RFIDclass::main() {
    bool cardDetected = mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();

    if (cardDetected) {
        lastDetectedTime = millis(); // Update the last detected time
        if (!cardPresent) {
            cardPresent = true;
            int cardNumber = getCardNumber();
            return cardNumber;  // Return the card number
        }
    } else {
        if (cardPresent && millis() - lastDetectedTime > debounceDelay) {
            cardPresent = false;
        }
    }

    return 0;  // Return 0 if no card is detected
}

int RFIDclass::getCardNumber() {
    byte card1UID[] = {0x04, 0x53, 0x63, 0x62, 0xEC, 0x6B, 0x80};  
    byte card2UID[] = {0x04, 0x56, 0x64, 0x62, 0xEC, 0x6B, 0x80};
    byte card3UID[] = {0x04, 0x4C, 0x64, 0x62, 0xEC, 0x6B, 0x80};

    Serial.print("UID tag: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) {
            Serial.print(" 0");
        } else {
            Serial.print(" ");
        }
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    if (compareUIDs(mfrc522.uid.uidByte, card1UID, mfrc522.uid.size)) {
        Serial.println("Found1");
        return 1;
    } else if (compareUIDs(mfrc522.uid.uidByte, card2UID, mfrc522.uid.size)) {
        Serial.println("Found2");
        return 2;
    } else if (compareUIDs(mfrc522.uid.uidByte, card3UID, mfrc522.uid.size)) {
        Serial.println("Found3");
        return 3;
    } else {
        Serial.println("None");
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

