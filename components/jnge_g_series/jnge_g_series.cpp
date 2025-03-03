#include "jnge_g_series.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace jnge_g_series {

static const char *const TAG = "jnge_g_series";

static const uint8_t READ_HOLDING_REGISTERS = 0x03;
static const uint8_t READ_INPUT_REGISTERS = 0x04;
static const uint8_t WRITE_SINGLE_REGISTER = 0x06;

void JngeGSeries::on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) {
  if (function == 0x12 && data.size() == 76) {
    this->on_status_data_(data);

    // The controller cannot handle two commands in series. The configuration
    // request is send here to decouple the requests.
    //
    // Request device configuration -> 0x06 0x16 0x10 0x24 0x00 0x27 0x4D 0x6F
    this->send(0x16, 0x1024, 0x27);

    return;
  }

  if (function == 0x16 && data.size() == 82) {
    this->on_configuration_data_(data);

    return;
  }

  ESP_LOGW(TAG, "Invalid size (%zu) for JN-G series inverter frame!", data.size());
}

void JngeGSeries::on_status_data_(const std::vector<uint8_t> &data) {
  auto jnge_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };
  auto jnge_get_32bit = [&](size_t i) -> uint32_t {
    return (uint32_t(jnge_get_16bit(i + 0)) << 16) | (uint32_t(jnge_get_16bit(i + 2)) << 0);
  };

  ESP_LOGI(TAG, "Status frame received");

  // ESP_LOGI(TAG, "Byte 0-1: %.0f (0x%04X)", jnge_get_16bit(0) * 1.0f, jnge_get_16bit(0));
  ESP_LOGI(TAG, "Byte 2-3: %.0f (0x%04X)", jnge_get_16bit(2) * 1.0f, jnge_get_16bit(2));

  ESP_LOGI(TAG, "AC voltage1: %.1f V", jnge_get_16bit(4) * 0.1f);

  ESP_LOGI(TAG, "Byte 6-7: %.0f (0x%04X)", jnge_get_16bit(6) * 1.0f, jnge_get_16bit(6));

  ESP_LOGI(TAG, "AC voltage2: %.1f V", jnge_get_16bit(8) * 0.1f);

  ESP_LOGI(TAG, "Byte 10-11: %.2f Hz (0x%04X)", jnge_get_16bit(10) * 0.01f, jnge_get_16bit(10));
  ESP_LOGI(TAG, "Byte 12-13: %.0f (0x%04X)", jnge_get_16bit(12) * 1.0f, jnge_get_16bit(12));
  ESP_LOGI(TAG, "Byte 14-15: %.0f (0x%04X) <-- What is this? (A)", jnge_get_16bit(14) * 1.0f, jnge_get_16bit(14));

  ESP_LOGI(TAG, "Battery voltage: %.1f V", jnge_get_16bit(16) * 0.1f);
  this->publish_state_(this->battery_voltage_sensor_, jnge_get_16bit(16) * 0.1f);

  ESP_LOGI(TAG, "Byte 18-19: %.1f (0x%04X) <-- What is this? (B)", jnge_get_16bit(18) * 0.1f, jnge_get_16bit(18));
  ESP_LOGI(TAG, "Byte 20-21: %.0f (0x%04X)", jnge_get_16bit(20) * 1.0f, jnge_get_16bit(20));
  ESP_LOGI(TAG, "Byte 22-23: %.0f (0x%04X)", jnge_get_16bit(22) * 1.0f, jnge_get_16bit(22));
  ESP_LOGI(TAG, "Byte 24-25: %.0f (0x%04X)", jnge_get_16bit(24) * 1.0f, jnge_get_16bit(24));
  ESP_LOGI(TAG, "Byte 26-27: %.0f (0x%04X)", jnge_get_16bit(26) * 1.0f, jnge_get_16bit(26));
  ESP_LOGI(TAG, "Byte 28-29: %.0f (0x%04X)", jnge_get_16bit(28) * 1.0f, jnge_get_16bit(28));
  ESP_LOGI(TAG, "Byte 30-31: %.0f (0x%04X)", jnge_get_16bit(30) * 1.0f, jnge_get_16bit(30));

  ESP_LOGI(TAG, "Byte 32-33: %.0f (0x%04X)", jnge_get_16bit(32) * 1.0f, jnge_get_16bit(32));
  ESP_LOGI(TAG, "Byte 32-35 - Total energy: %.1f kWh", jnge_get_32bit(32) * 0.1f);

  ESP_LOGI(TAG, "Byte 36-37: %.0f (0x%04X)", jnge_get_16bit(36) * 1.0f, jnge_get_16bit(36));
  ESP_LOGI(TAG, "Byte 38-39: %.0f (0x%04X)", jnge_get_16bit(38) * 1.0f, jnge_get_16bit(38));
  ESP_LOGI(TAG, "Byte 40-41: %.0f (0x%04X)", jnge_get_16bit(40) * 1.0f, jnge_get_16bit(40));
  ESP_LOGI(TAG, "Byte 42-43: %.0f (0x%04X)", jnge_get_16bit(42) * 1.0f, jnge_get_16bit(42));
  ESP_LOGI(TAG, "Byte 44-45: %.0f (0x%04X)", jnge_get_16bit(44) * 1.0f, jnge_get_16bit(44));
  ESP_LOGI(TAG, "Byte 46-47: %.0f (0x%04X)", jnge_get_16bit(46) * 1.0f, jnge_get_16bit(46));
  ESP_LOGI(TAG, "Byte 48-49: %.0f (0x%04X)", jnge_get_16bit(48) * 1.0f, jnge_get_16bit(48));
  ESP_LOGI(TAG, "Byte 50-51: %.0f (0x%04X)", jnge_get_16bit(50) * 1.0f, jnge_get_16bit(50));
  ESP_LOGI(TAG, "Byte 52-53: %.0f (0x%04X)", jnge_get_16bit(52) * 1.0f, jnge_get_16bit(52));
  ESP_LOGI(TAG, "Byte 54-55: %.0f (0x%04X)", jnge_get_16bit(54) * 1.0f, jnge_get_16bit(54));
  ESP_LOGI(TAG, "Byte 56-57: %.0f (0x%04X)", jnge_get_16bit(56) * 1.0f, jnge_get_16bit(56));
  ESP_LOGI(TAG, "Byte 58-59: %.0f (0x%04X)", jnge_get_16bit(58) * 1.0f, jnge_get_16bit(58));
  ESP_LOGI(TAG, "Byte 60-61: %.0f (0x%04X)", jnge_get_16bit(60) * 1.0f, jnge_get_16bit(60));
  ESP_LOGI(TAG, "Byte 62-63: %.0f (0x%04X)", jnge_get_16bit(62) * 1.0f, jnge_get_16bit(62));
  ESP_LOGI(TAG, "Byte 64-65: %.0f (0x%04X)", jnge_get_16bit(64) * 1.0f, jnge_get_16bit(64));
  ESP_LOGI(TAG, "Byte 66-67: %.0f (0x%04X)", jnge_get_16bit(66) * 1.0f, jnge_get_16bit(66));
  ESP_LOGI(TAG, "Byte 68-69: %.0f (0x%04X)", jnge_get_16bit(68) * 1.0f, jnge_get_16bit(68));
  ESP_LOGI(TAG, "Byte 70-71: %.0f (0x%04X)", jnge_get_16bit(70) * 1.0f, jnge_get_16bit(70));
  ESP_LOGI(TAG, "Byte 72-73: %.0f (0x%04X)", jnge_get_16bit(72) * 1.0f, jnge_get_16bit(72));
  ESP_LOGI(TAG, "Byte 74-75: %.0f (0x%04X)", jnge_get_16bit(74) * 1.0f, jnge_get_16bit(74));

  this->no_response_count_ = 0;
}

void JngeGSeries::on_configuration_data_(const std::vector<uint8_t> &data) {
  // auto jnge_get_16bit = [&](size_t i) -> uint16_t {
  //     return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  // };

  ESP_LOGI(TAG, "Config frame received");
}

void JngeGSeries::on_write_data_(const std::vector<uint8_t> &data) {
  ESP_LOGI(TAG, "Write register response received: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void JngeGSeries::write_register(uint16_t address, uint16_t value) {
  // Example writer register request
  // 0x06 0x18 0x10 0x38 0x12 0x34 0xA8 0x05
  // 0x06 0x18 0x10 0x37 0x12 0x34 0x98 0x06
  this->send(0x18, address, value);

  ESP_LOGI(TAG, "Write register request: 0x%02X 0x%02X 0x%02X 0x%02X (4)", (uint8_t) (address >> 8), (uint8_t) address,
           (uint8_t) (value >> 8), (uint8_t) value);
}

void JngeGSeries::publish_device_offline_() {
  this->publish_state_(this->operation_mode_id_sensor_, -1);
  this->publish_state_(this->operation_mode_text_sensor_, "Offline");
}

void JngeGSeries::update() {
  if (this->no_response_count_ >= NO_RESPONSE_THRESHOLD) {
    this->publish_device_offline_();
    ESP_LOGW(TAG, "The device didn't respond to the last %d status requests", this->no_response_count_);
    this->no_response_count_ = 0;
  }
  no_response_count_++;

  // Request device status -> 0x06, 0x12, 0x10, 0x00, 0x00, 0x24, 0xBC, 0xA5
  this->send(0x12, 0x1000, 0x24);
}

void JngeGSeries::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;

  binary_sensor->publish_state(state);
}

void JngeGSeries::publish_state_(number::Number *number, float value) {
  if (number == nullptr)
    return;

  number->publish_state(value);
}

void JngeGSeries::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void JngeGSeries::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;

  text_sensor->publish_state(state);
}

void JngeGSeries::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "JngeGSeries:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("", "Battery Voltage", this->battery_voltage_sensor_);
}

}  // namespace jnge_g_series
}  // namespace esphome
