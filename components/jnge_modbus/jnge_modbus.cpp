#include "jnge_modbus.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jnge_modbus {

static const char *const TAG = "jnge_modbus";

static const uint8_t WRITE_SINGLE_REGISTER = 0x06;

void JngeModbus::setup() {
  if (this->flow_control_pin_ != nullptr) {
    this->flow_control_pin_->setup();
  }
}
void JngeModbus::loop() {
  const uint32_t now = millis();
  if (now - this->last_jnge_modbus_byte_ > 50) {
    this->rx_buffer_.clear();
    this->last_jnge_modbus_byte_ = now;
  }

  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);
    if (this->parse_jnge_modbus_byte_(byte)) {
      this->last_jnge_modbus_byte_ = now;
    } else {
      this->rx_buffer_.clear();
    }
  }
}

uint16_t crc16(const uint8_t *data, uint8_t len) {
  uint16_t crc = 0xFFFF;
  while (len--) {
    crc ^= *data++;
    for (uint8_t i = 0; i < 8; i++) {
      if ((crc & 0x01) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

bool JngeModbus::parse_jnge_modbus_byte_(uint8_t byte) {
  size_t at = this->rx_buffer_.size();
  this->rx_buffer_.push_back(byte);
  const uint8_t *raw = &this->rx_buffer_[0];

  // Byte 0: jnge_modbus address (match all)
  if (at == 0)
    return true;
  uint8_t address = raw[0];

  // Byte 1: Function (msb indicates error)
  if (at == 1)
    return (byte & 0x80) != 0x80;
  uint8_t function = raw[1];

  // Byte 2: Size (with jnge_modbus rtu function code 4/3)
  // See also https://en.wikipedia.org/wiki/Modbus
  if (at == 2)
    return true;

  uint8_t data_len = raw[2];
  uint8_t data_offset = 3;
  // function 0x06 jnge frames has a fixed size without data_len
  if (function == WRITE_SINGLE_REGISTER) {
    data_offset = 2;
    data_len = 4;
  }

  // Byte 3..3+data_len-1: Data
  if (at < data_offset + data_len)
    return true;

  // Byte 3+data_len: CRC_LO (over all bytes)
  if (at == data_offset + data_len)
    return true;
  // Byte 3+len+1: CRC_HI (over all bytes)
  uint16_t computed_crc = crc16(raw, data_offset + data_len);
  uint16_t remote_crc = uint16_t(raw[data_offset + data_len]) | (uint16_t(raw[data_offset + data_len + 1]) << 8);
  if (computed_crc != remote_crc) {
    ESP_LOGW(TAG, "CRC check failed! 0x%04X != 0x%04X", computed_crc, remote_crc);
    return false;
  }

  std::vector<uint8_t> data(this->rx_buffer_.begin() + data_offset, this->rx_buffer_.begin() + data_offset + data_len);

  bool found = false;
  for (auto *device : this->devices_) {
    if (device->address_ == address) {
      device->on_jnge_modbus_data(function, data);
      found = true;
    }
  }
  if (!found) {
    ESP_LOGW(TAG, "Got JngeModbus frame from unknown address 0x%02X!", address);
  }

  // return false to reset buffer
  return false;
}

void JngeModbus::dump_config() {
  ESP_LOGCONFIG(TAG, "JngeModbus:");
  LOG_PIN("  Flow Control Pin: ", this->flow_control_pin_);
}
float JngeModbus::get_setup_priority() const {
  // After UART bus
  return setup_priority::BUS - 1.0f;
}
void JngeModbus::send(uint8_t address, uint8_t function, uint16_t start_address, uint16_t register_count) {
  uint8_t frame[8];
  frame[0] = address;
  frame[1] = function;
  frame[2] = start_address >> 8;
  frame[3] = start_address >> 0;
  frame[4] = register_count >> 8;
  frame[5] = register_count >> 0;
  auto crc = crc16(frame, 6);
  frame[6] = crc >> 0;
  frame[7] = crc >> 8;

  if (this->flow_control_pin_ != nullptr)
    this->flow_control_pin_->digital_write(true);

  this->write_array(frame, 8);
  this->flush();

  if (this->flow_control_pin_ != nullptr)
    this->flow_control_pin_->digital_write(false);
}

}  // namespace jnge_modbus
}  // namespace esphome
