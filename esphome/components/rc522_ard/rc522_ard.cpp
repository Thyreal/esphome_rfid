#include "rc522_ard.h"

RC522Ard::RC522Ard(uint8_t ssPin, uint8_t rstPin) : mfrc522(ssPin, rstPin), serial(&Serial) {
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("RFID-Leser bereit...");
}

void RC522Ard::begin() {
    // Keine zusätzliche Initialisierung benötigt
}

void RC522Ard::loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
    serial->print("RFID UID: ");
    serial->println(uid);
}

String RC522Ard::readRFIDUID() {
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return "";
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return "";
    }
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
    return uid;
}
