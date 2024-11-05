#pragma once

#include "esphome.h"

class MMWaveSensor : public Component, public UARTDevice {
 public:
  Sensor *target_distance_sensor = new Sensor();
  Sensor *motion_energy_sensor = new Sensor();
  Sensor *target_state_sensor = new Sensor();

  MMWaveSensor(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // Initialization code if needed
  }

  void loop() override {
    while (available()) {
      if (read() == 0xF4 && read() == 0xF3 && read() == 0xF2 && read() == 0xF1) {
        uint16_t length = read() | (read() << 8);
        if (length == 13 && read() == 0x02 && read() == 0xAA) {
          uint8_t target_state = read();
          uint16_t target_distance = read() | (read() << 8);
          uint8_t motion_energy = read();
          
          // Skip the rest of the data
          for (int i = 0; i < 5; i++) read();
          
          if (read() == 0xF8 && read() == 0xF7 && read() == 0xF6 && read() == 0xF5) {
            target_state_sensor->publish_state(target_state);
            target_distance_sensor->publish_state(target_distance / 100.0);
            motion_energy_sensor->publish_state(motion_energy);
          }
        }
      }
    }
  }
};