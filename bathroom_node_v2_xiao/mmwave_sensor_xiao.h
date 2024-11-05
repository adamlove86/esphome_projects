#include "esphome.h"

class MmwaveSensorXiao : public PollingComponent, public UARTDevice {
 public:
  Sensor *presence = new Sensor();
  Sensor *motion_energy = new Sensor();
  Sensor *stationary_energy = new Sensor();

  MmwaveSensorXiao(UARTComponent *parent) : PollingComponent(1000), UARTDevice(parent) {}

  void setup() override {
    // Initialization if necessary
  }

  void update() override {
    // Read and process sensor data over UART
    const int max_length = 100;
    uint8_t buffer[max_length];
    size_t length = read_array(buffer, max_length);

    if (length > 0) {
      float presence_val = parse_presence(buffer, length);
      float motion_energy_val = parse_motion_energy(buffer, length);
      float stationary_energy_val = parse_stationary_energy(buffer, length);

      presence->publish_state(presence_val);
      motion_energy->publish_state(motion_energy_val);
      stationary_energy->publish_state(stationary_energy_val);
    }
  }

 private:
  float parse_presence(const uint8_t *buffer, size_t length) {
    // Parse presence
    return static_cast<float>(buffer[0]);
  }

  float parse_motion_energy(const uint8_t *buffer, size_t length) {
    // Parse motion energy
    return static_cast<float>(buffer[1]);
  }

  float parse_stationary_energy(const uint8_t *buffer, size_t length) {
    // Parse stationary energy
    return static_cast<float>(buffer[2]);
  }
};