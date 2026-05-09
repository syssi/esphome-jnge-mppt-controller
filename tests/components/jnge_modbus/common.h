#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/jnge_modbus/jnge_modbus.h"

namespace esphome::jnge_modbus::testing {

class MockJngeModbusDevice : public JngeModbusDevice {
 public:
  uint8_t last_function{0xFF};
  std::vector<uint8_t> received_data;
  int call_count{0};

  void on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) override {
    last_function = function;
    received_data = data;
    call_count++;
  }
};

class TestableJngeModbus : public JngeModbus {
 public:
  void loop() override {}
  using JngeModbus::parse_jnge_modbus_byte_;

  bool feed(const std::vector<uint8_t> &frame) {
    bool result = false;
    for (uint8_t byte : frame)
      result = parse_jnge_modbus_byte_(byte);
    return result;
  }
};

// Build a valid response frame with CRC.
// Format: [addr, func, data_len, data..., crc_lo, crc_hi]
inline std::vector<uint8_t> make_response_frame(uint8_t address, uint8_t function,
                                                 const std::vector<uint8_t> &data) {
  std::vector<uint8_t> frame;
  frame.push_back(address);
  frame.push_back(function);
  frame.push_back(static_cast<uint8_t>(data.size()));
  frame.insert(frame.end(), data.begin(), data.end());
  uint16_t crc = crc16(frame.data(), static_cast<uint8_t>(frame.size()));
  frame.push_back(static_cast<uint8_t>(crc & 0xFF));
  frame.push_back(static_cast<uint8_t>(crc >> 8));
  return frame;
}

}  // namespace esphome::jnge_modbus::testing
