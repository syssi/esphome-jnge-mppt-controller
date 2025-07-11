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
    // Request device configuration -> 0x06 0x16 0x10 0x00 0x00 0x29 0x8C 0xA0
    this->send(0x16, 0x1000, 41);

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

  ESP_LOGI(TAG, "Status frame received (%d bytes)", data.size());

  for (size_t i = 0; i < data.size(); i = i + 2) {
    if (i == 4 || i == 8 || i == 10 || i == 14 || i == 16 || i == 32 || i == 36) {
      continue;
    }

    ESP_LOGD(TAG, "Status Byte %2d-%2d: %5.0f (0x%04X)", i, i + 1, jnge_get_16bit(i) * 1.0f, jnge_get_16bit(i));
  }

  float ac_voltage1 = jnge_get_16bit(4) * 0.1f;
  this->publish_state_(this->ac_voltage1_sensor_, ac_voltage1);

  this->publish_state_(this->ac_voltage2_sensor_, jnge_get_16bit(8) * 0.1f);
  this->publish_state_(this->ac_frequency_sensor_, jnge_get_16bit(10) * 0.01f);

  float ac_current = jnge_get_16bit(14) * 0.01f;
  this->publish_state_(this->ac_current_sensor_, ac_current);
  this->publish_state_(this->ac_output_power_sensor_, ac_voltage1 * ac_current);

  this->publish_state_(this->battery_voltage_sensor_, jnge_get_16bit(16) * 0.1f);
  this->publish_state_(this->inverter_temperature_sensor_, jnge_get_16bit(18) * 0.1f);
  this->publish_state_(this->total_energy_sensor_, jnge_get_32bit(32) * 0.1f);
  ESP_LOGD(TAG, "Total energy 2:   %.1f", jnge_get_16bit(34) * 0.1f);
  this->publish_state_(this->ac_output_load_sensor_, (float) jnge_get_16bit(36) * 0.1f);

  this->no_response_count_ = 0;
}

void JngeGSeries::on_configuration_data_(const std::vector<uint8_t> &data) {
  auto jnge_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  ESP_LOGI(TAG, "Config frame received (%d bytes)", data.size());

  for (size_t i = 0; i < data.size(); i = i + 2) {
    ESP_LOGD(TAG, "Config Byte %2d-%2d: %5.0f (0x%04X)", i, i + 1, jnge_get_16bit(i) * 1.0f, jnge_get_16bit(i));
  }
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
  this->publish_state_(this->ac_voltage1_sensor_, NAN);
  this->publish_state_(this->ac_voltage2_sensor_, NAN);
  this->publish_state_(this->ac_frequency_sensor_, NAN);
  this->publish_state_(this->ac_current_sensor_, NAN);
  this->publish_state_(this->battery_voltage_sensor_, NAN);
  this->publish_state_(this->total_energy_sensor_, NAN);
  this->publish_state_(this->inverter_temperature_sensor_, NAN);
  this->publish_state_(this->ac_output_load_sensor_, NAN);
  this->publish_state_(this->ac_output_power_sensor_, NAN);
}

void JngeGSeries::update() {
  if (this->no_response_count_ >= NO_RESPONSE_THRESHOLD) {
    this->publish_device_offline_();
    ESP_LOGW(TAG, "The device didn't respond to the last %d status requests", this->no_response_count_);
    this->no_response_count_ = 0;
  }
  no_response_count_++;

  // Request device status -> 0x06 0x12 0x10 0x00 0x00 0x26 0x3D 0x64
  this->send(0x12, 0x1000, 38);
}

void JngeGSeries::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void JngeGSeries::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "JngeGSeries:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("", "AC Voltage 1", this->ac_voltage1_sensor_);
  LOG_SENSOR("", "AC Voltage 2", this->ac_voltage2_sensor_);
  LOG_SENSOR("", "AC Frequency", this->ac_frequency_sensor_);
  LOG_SENSOR("", "AC Current", this->ac_current_sensor_);
  LOG_SENSOR("", "Battery Voltage", this->battery_voltage_sensor_);
  LOG_SENSOR("", "Total Energy", this->total_energy_sensor_);
  LOG_SENSOR("", "Inverter Temperature", this->inverter_temperature_sensor_);
  LOG_SENSOR("", "AC Output Load", this->ac_output_load_sensor_);
  LOG_SENSOR("", "AC Output Power", this->ac_output_power_sensor_);
}

}  // namespace jnge_g_series
}  // namespace esphome
