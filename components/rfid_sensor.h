#ifndef RFID_SENSOR_H
#define RFID_SENSOR_H

#include "esphome.h"

class RFIDSensor : public PollingComponent, public Sensor {
 public:
  Sensor *uid_sensor = new Sensor();

  RFIDSensor() : PollingComponent(1000) {}

  void setup() override {
    // Initialisierungscode
  }

  void update() override {
    // Code zum Lesen der RFID-Daten vom UART
    while (available()) {
      std::string data = read_line();
      if (!data.empty()) {
        uid_sensor->publish_state(data.c_str());
      }
    }
  }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void dump_config() override {
    ESP_LOGCONFIG(TAG, "RFID Sensor");
  }
};

#endif // RFID_SENSOR_H
