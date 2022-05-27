#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/select/select.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/jnge_modbus/jnge_modbus.h"

namespace esphome {
namespace jnge_wind_solar_controller {

static const uint8_t NO_RESPONSE_THRESHOLD = 15;

class JngeWindSolarController : public PollingComponent, public jnge_modbus::JngeModbusDevice {
 public:
  void set_load_detected_binary_sensor(binary_sensor::BinarySensor *load_detected_binary_sensor) {
    load_detected_binary_sensor_ = load_detected_binary_sensor;
  }
  void set_load_binary_sensor(binary_sensor::BinarySensor *load_binary_sensor) {
    load_binary_sensor_ = load_binary_sensor;
  }
  void set_charging_binary_sensor(binary_sensor::BinarySensor *charging_binary_sensor) {
    charging_binary_sensor_ = charging_binary_sensor;
  }

  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) {
    firmware_version_sensor_ = firmware_version_sensor;
  }
  void set_peak_pv_charging_rating_sensor(sensor::Sensor *peak_pv_charging_rating_sensor) {
    peak_pv_charging_rating_sensor_ = peak_pv_charging_rating_sensor;
  }
  void set_peak_fan_charging_rating_sensor(sensor::Sensor *peak_fan_charging_rating_sensor) {
    peak_fan_charging_rating_sensor_ = peak_fan_charging_rating_sensor;
  }
  void set_pv_voltage_sensor(sensor::Sensor *pv_voltage_sensor) { pv_voltage_sensor_ = pv_voltage_sensor; }
  void set_fan_voltage_sensor(sensor::Sensor *fan_voltage_sensor) { fan_voltage_sensor_ = fan_voltage_sensor; }
  void set_battery_voltage_sensor(sensor::Sensor *battery_voltage_sensor) {
    battery_voltage_sensor_ = battery_voltage_sensor;
  }
  void set_pv_charging_current_sensor(sensor::Sensor *pv_charging_current_sensor) {
    pv_charging_current_sensor_ = pv_charging_current_sensor;
  }
  void set_fan_charging_current_sensor(sensor::Sensor *fan_charging_current_sensor) {
    fan_charging_current_sensor_ = fan_charging_current_sensor;
  }
  void set_pv_charging_power_sensor(sensor::Sensor *pv_charging_power_sensor) {
    pv_charging_power_sensor_ = pv_charging_power_sensor;
  }
  void set_fan_charging_power_sensor(sensor::Sensor *fan_charging_power_sensor) {
    fan_charging_power_sensor_ = fan_charging_power_sensor;
  }
  void set_pv_total_energy_sensor(sensor::Sensor *pv_total_energy_sensor) {
    pv_total_energy_sensor_ = pv_total_energy_sensor;
  }
  void set_fan_total_energy_sensor(sensor::Sensor *fan_total_energy_sensor) {
    fan_total_energy_sensor_ = fan_total_energy_sensor;
  }
  void set_operation_mode_id_sensor(sensor::Sensor *operation_mode_id_sensor) {
    operation_mode_id_sensor_ = operation_mode_id_sensor;
  }
  void set_error_bitmask_sensor(sensor::Sensor *error_bitmask_sensor) { error_bitmask_sensor_ = error_bitmask_sensor; }
  void set_battery_voltage_level_sensor(sensor::Sensor *battery_voltage_level_sensor) {
    battery_voltage_level_sensor_ = battery_voltage_level_sensor;
  }
  void set_battery_strings_sensor(sensor::Sensor *battery_strings_sensor) {
    battery_strings_sensor_ = battery_strings_sensor;
  }

  void set_operation_mode_text_sensor(text_sensor::TextSensor *operation_mode_text_sensor) {
    operation_mode_text_sensor_ = operation_mode_text_sensor;
  }
  void set_errors_text_sensor(text_sensor::TextSensor *errors_text_sensor) { errors_text_sensor_ = errors_text_sensor; }
  void set_battery_type_text_sensor(text_sensor::TextSensor *battery_type_text_sensor) {
    battery_type_text_sensor_ = battery_type_text_sensor;
  }

  void set_street_light_mode_switch(switch_::Switch *street_light_mode_switch) {
    street_light_mode_switch_ = street_light_mode_switch;
  }
  void set_charging_switch(switch_::Switch *charging_switch) { charging_switch_ = charging_switch; }
  void set_load_switch(switch_::Switch *load_switch) { load_switch_ = load_switch; }

  void set_enable_fake_traffic(bool enable_fake_traffic) { enable_fake_traffic_ = enable_fake_traffic; }

  void dump_config() override;

  void on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  binary_sensor::BinarySensor *load_detected_binary_sensor_;
  binary_sensor::BinarySensor *load_binary_sensor_;
  binary_sensor::BinarySensor *charging_binary_sensor_;

  // status
  sensor::Sensor *firmware_version_sensor_;
  sensor::Sensor *peak_pv_charging_rating_sensor_;
  sensor::Sensor *peak_fan_charging_rating_sensor_;
  sensor::Sensor *pv_voltage_sensor_;
  sensor::Sensor *fan_voltage_sensor_;
  sensor::Sensor *battery_voltage_sensor_;
  sensor::Sensor *pv_charging_current_sensor_;
  sensor::Sensor *fan_charging_current_sensor_;
  sensor::Sensor *pv_charging_power_sensor_;
  sensor::Sensor *fan_charging_power_sensor_;
  sensor::Sensor *pv_total_energy_sensor_;
  sensor::Sensor *fan_total_energy_sensor_;
  sensor::Sensor *operation_mode_id_sensor_;
  sensor::Sensor *battery_strings_sensor_;
  sensor::Sensor *battery_voltage_level_sensor_;
  sensor::Sensor *error_bitmask_sensor_;

  switch_::Switch *street_light_mode_switch_;
  switch_::Switch *charging_switch_;
  switch_::Switch *load_switch_;

  text_sensor::TextSensor *operation_mode_text_sensor_;
  text_sensor::TextSensor *errors_text_sensor_;
  text_sensor::TextSensor *battery_type_text_sensor_;

  bool enable_fake_traffic_;
  uint8_t no_response_count_ = 0;

  void on_read_registers_data_(const std::vector<uint8_t> &data);
  void on_write_single_register_data_(const std::vector<uint8_t> &data);
  void on_write_data_(const std::vector<uint8_t> &data);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_device_offline_();
  std::string error_bits_to_string_(uint16_t bitmask);
};

}  // namespace jnge_wind_solar_controller
}  // namespace esphome
