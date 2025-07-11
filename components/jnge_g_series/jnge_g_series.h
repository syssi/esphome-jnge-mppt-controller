#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/jnge_modbus/jnge_modbus.h"

namespace esphome {
namespace jnge_g_series {

static const uint8_t NO_RESPONSE_THRESHOLD = 15;

class JngeGSeries : public PollingComponent, public jnge_modbus::JngeModbusDevice {
 public:
  void set_battery_voltage_sensor(sensor::Sensor *battery_voltage_sensor) {
    battery_voltage_sensor_ = battery_voltage_sensor;
  }
  void set_ac_voltage1_sensor(sensor::Sensor *ac_voltage1_sensor) { ac_voltage1_sensor_ = ac_voltage1_sensor; }
  void set_ac_voltage2_sensor(sensor::Sensor *ac_voltage2_sensor) { ac_voltage2_sensor_ = ac_voltage2_sensor; }
  void set_ac_frequency_sensor(sensor::Sensor *ac_frequency_sensor) { ac_frequency_sensor_ = ac_frequency_sensor; }
  void set_ac_current_sensor(sensor::Sensor *ac_current_sensor) { ac_current_sensor_ = ac_current_sensor; }
  void set_total_energy_sensor(sensor::Sensor *total_energy_sensor) { total_energy_sensor_ = total_energy_sensor; }
  void set_inverter_temperature_sensor(sensor::Sensor *inverter_temperature_sensor) {
    inverter_temperature_sensor_ = inverter_temperature_sensor;
  }
  void set_ac_output_load_sensor(sensor::Sensor *ac_output_load_sensor) {
    ac_output_load_sensor_ = ac_output_load_sensor;
  }
  void set_ac_output_power_sensor(sensor::Sensor *ac_output_power_sensor) {
    ac_output_power_sensor_ = ac_output_power_sensor;
  }

  void dump_config() override;

  void on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  sensor::Sensor *battery_voltage_sensor_;
  sensor::Sensor *ac_voltage1_sensor_;
  sensor::Sensor *ac_voltage2_sensor_;
  sensor::Sensor *ac_frequency_sensor_;
  sensor::Sensor *ac_current_sensor_;
  sensor::Sensor *total_energy_sensor_;
  sensor::Sensor *inverter_temperature_sensor_;
  sensor::Sensor *ac_output_load_sensor_;
  sensor::Sensor *ac_output_power_sensor_;

  uint8_t no_response_count_ = 0;

  void on_status_data_(const std::vector<uint8_t> &data);
  void on_configuration_data_(const std::vector<uint8_t> &data);
  void on_write_data_(const std::vector<uint8_t> &data);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_device_offline_();
};

}  // namespace jnge_g_series
}  // namespace esphome
