#ifndef RC522_ARD_H
#define RC522_ARD_H

#include <Arduino.h>
#include <SPI.h>
#include "components/rc522/rc522.h"  // Relativer Pfad zu rc522.h

class RC522Ard {
public:
    RC522Ard(uint8_t ssPin, uint8_t rstPin);
    void begin();
    void loop();
    String readRFIDUID();

private:
    MFRC522 mfrc522;
    HardwareSerial *serial;
};

#endif // RC522_ARD_H
