#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool cardPresent = false;  // Track the state of card presence
unsigned long lastDetectedTime = 0;
unsigned long debounceDelay = 50; // Debounce time in milliseconds

// Define card UIDs
byte card1UID[] = {0xE3, 0xDF, 0xF2, 0xF4};
byte card2UID[] = {0x85, 0x12, 0x46, 0x70};
byte card3UID[] = {0xF5, 0xDF, 0x43, 0x70};

void setup() {
  Serial.begin(9600);    // Initialize serial communications
  SPI.begin();           // Initialize SPI bus
  mfrc522.PCD_Init();    // Initialize MFRC522
  Serial.println("Scan an RFID card/tag");
}

void loop() {
  bool cardDetected = mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();

  if (cardDetected) {
    lastDetectedTime = millis(); // Update the last detected time
    if (!cardPresent) {
      cardPresent = true;
      Serial.println("Card detected");
      printCardNumber();
    }
  } else {
    if (cardPresent && millis() - lastDetectedTime > debounceDelay) {
      cardPresent = false;
      Serial.println("Card removed");
    }
  }

}

void printCardNumber() {
  if (compareUIDs(mfrc522.uid.uidByte, card1UID, mfrc522.uid.size)) {
    Serial.println("Card 1");
  } else if (compareUIDs(mfrc522.uid.uidByte, card2UID, mfrc522.uid.size)) {
    Serial.println("Card 2");
  } else if (compareUIDs(mfrc522.uid.uidByte, card3UID, mfrc522.uid.size)) {
    Serial.println("Card 3");
  } else {
    Serial.println("Unknown card");
  }
}

bool compareUIDs(byte *uid1, byte *uid2, byte size) {
  for (byte i = 0; i < size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
