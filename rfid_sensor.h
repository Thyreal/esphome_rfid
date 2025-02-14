#ifndef RFID_SENSOR_H
#define RFID_SENSOR_H

#include "esphome.h"

class RFIDSensor : public Component, public UARTDevice {
 public:
  Sensor *uid_sensor = new Sensor();

  RFIDSensor(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // Initialisierungscode
  }

  void loop() override {
    // Code zum Lesen der RFID-Daten vom UART
    while (available()) {
      std::string data = read_line();
      if (!data.empty()) {
        uid_sensor->publish_state(data.c_str());
      }
    }
  }

  void dump_config() override {
    ESP_LOGCONFIG(TAG, "RFID Sensor");
  }
};

#endif // RFID_SENSOR_H
