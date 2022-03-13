#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/jnge_modbus/jnge_modbus.h"

namespace esphome {
namespace jnge_mppt_controller {

class JngeMpptController : public PollingComponent, public jnge_modbus::JngeModbusDevice {
 public:
  void set_load_detected_binary_sensor(binary_sensor::BinarySensor *load_detected_binary_sensor) {
    load_detected_binary_sensor_ = load_detected_binary_sensor;
  }
  void set_fan_running_binary_sensor(binary_sensor::BinarySensor *fan_running_binary_sensor) {
    fan_running_binary_sensor_ = fan_running_binary_sensor;
  }
  void set_charging_binary_sensor(binary_sensor::BinarySensor *charging_binary_sensor) {
    charging_binary_sensor_ = charging_binary_sensor;
  }
  void set_load_binary_sensor(binary_sensor::BinarySensor *load_binary_sensor) {
    load_binary_sensor_ = load_binary_sensor;
  }

  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) {
    firmware_version_sensor_ = firmware_version_sensor;
  }
  void set_pv_voltage_sensor(sensor::Sensor *pv_voltage_sensor) { pv_voltage_sensor_ = pv_voltage_sensor; }
  void set_battery_voltage_sensor(sensor::Sensor *battery_voltage_sensor) {
    battery_voltage_sensor_ = battery_voltage_sensor;
  }
  void set_channel_a_current_sensor(sensor::Sensor *channel_a_current_sensor) {
    channel_a_current_sensor_ = channel_a_current_sensor;
  }
  void set_channel_b_current_sensor(sensor::Sensor *channel_b_current_sensor) {
    channel_b_current_sensor_ = channel_b_current_sensor;
  }
  void set_charging_current_sensor(sensor::Sensor *charging_current_sensor) {
    charging_current_sensor_ = charging_current_sensor;
  }
  void set_charger_temperature_sensor(sensor::Sensor *charger_temperature_sensor) {
    charger_temperature_sensor_ = charger_temperature_sensor;
  }
  void set_charging_power_sensor(sensor::Sensor *charging_power_sensor) {
    charging_power_sensor_ = charging_power_sensor;
  }
  void set_discharge_power_sensor(sensor::Sensor *discharge_power_sensor) {
    discharge_power_sensor_ = discharge_power_sensor;
  }
  void set_battery_capacity_sensor(sensor::Sensor *battery_capacity_sensor) {
    battery_capacity_sensor_ = battery_capacity_sensor;
  }
  void set_operation_mode_id_sensor(sensor::Sensor *operation_mode_id_sensor) {
    operation_mode_id_sensor_ = operation_mode_id_sensor;
  }
  void set_discharge_current_sensor(sensor::Sensor *discharge_current_sensor) {
    discharge_current_sensor_ = discharge_current_sensor;
  }
  void set_discharge_times_sensor(sensor::Sensor *discharge_times_sensor) {
    discharge_times_sensor_ = discharge_times_sensor;
  }
  void set_total_charging_energy_sensor(sensor::Sensor *total_charging_energy_sensor) {
    total_charging_energy_sensor_ = total_charging_energy_sensor;
  }
  void set_total_discharge_energy_sensor(sensor::Sensor *total_discharge_energy_sensor) {
    total_discharge_energy_sensor_ = total_discharge_energy_sensor;
  }
  void set_battery_temperature_sensor(sensor::Sensor *battery_temperature_sensor) {
    battery_temperature_sensor_ = battery_temperature_sensor;
  }
  void set_error_bitmask_sensor(sensor::Sensor *error_bitmask_sensor) { error_bitmask_sensor_ = error_bitmask_sensor; }
  void set_controller_voltage_level_sensor(sensor::Sensor *controller_voltage_level_sensor) {
    controller_voltage_level_sensor_ = controller_voltage_level_sensor;
  }
  void set_pv_standby_voltage_sensor(sensor::Sensor *pv_standby_voltage_sensor) {
    pv_standby_voltage_sensor_ = pv_standby_voltage_sensor;
  }
  void set_controller_current_level_sensor(sensor::Sensor *controller_current_level_sensor) {
    controller_current_level_sensor_ = controller_current_level_sensor;
  }
  void set_battery_strings_sensor(sensor::Sensor *battery_strings_sensor) {
    battery_strings_sensor_ = battery_strings_sensor;
  }
  void set_battery_temperature_compensation_voltage_point_sensor(
      sensor::Sensor *battery_temperature_compensation_voltage_point_sensor) {
    battery_temperature_compensation_voltage_point_sensor_ = battery_temperature_compensation_voltage_point_sensor;
  }

  // configuration
  void set_battery_overvoltage_sensor(sensor::Sensor *battery_overvoltage_sensor) {
    battery_overvoltage_sensor_ = battery_overvoltage_sensor;
  }
  void set_charging_limit_voltage_sensor(sensor::Sensor *charging_limit_voltage_sensor) {
    charging_limit_voltage_sensor_ = charging_limit_voltage_sensor;
  }
  void set_battery_overvoltage_recovery_sensor(sensor::Sensor *battery_overvoltage_recovery_sensor) {
    battery_overvoltage_recovery_sensor_ = battery_overvoltage_recovery_sensor;
  }
  void set_equalizing_charging_voltage_sensor(sensor::Sensor *equalizing_charging_voltage_sensor) {
    equalizing_charging_voltage_sensor_ = equalizing_charging_voltage_sensor;
  }
  void set_boost_charging_voltage_sensor(sensor::Sensor *boost_charging_voltage_sensor) {
    boost_charging_voltage_sensor_ = boost_charging_voltage_sensor;
  }
  void set_boost_charging_return_voltage_sensor(sensor::Sensor *boost_charging_return_voltage_sensor) {
    boost_charging_return_voltage_sensor_ = boost_charging_return_voltage_sensor;
  }
  void set_floating_charge_voltage_sensor(sensor::Sensor *floating_charge_voltage_sensor) {
    floating_charge_voltage_sensor_ = floating_charge_voltage_sensor;
  }
  void set_over_discharge_voltage_sensor(sensor::Sensor *over_discharge_voltage_sensor) {
    over_discharge_voltage_sensor_ = over_discharge_voltage_sensor;
  }
  void set_over_discharge_recovery_voltage_sensor(sensor::Sensor *over_discharge_recovery_voltage_sensor) {
    over_discharge_recovery_voltage_sensor_ = over_discharge_recovery_voltage_sensor;
  }
  void set_battery_undervoltage_sensor(sensor::Sensor *battery_undervoltage_sensor) {
    battery_undervoltage_sensor_ = battery_undervoltage_sensor;
  }
  void set_equalization_charging_time_sensor(sensor::Sensor *equalization_charging_time_sensor) {
    equalization_charging_time_sensor_ = equalization_charging_time_sensor;
  }
  void set_improve_charging_time_sensor(sensor::Sensor *improve_charging_time_sensor) {
    improve_charging_time_sensor_ = improve_charging_time_sensor;
  }
  void set_temperature_compensation_coefficient_sensor(sensor::Sensor *temperature_compensation_coefficient_sensor) {
    temperature_compensation_coefficient_sensor_ = temperature_compensation_coefficient_sensor;
  }
  void set_device_address_sensor(sensor::Sensor *device_address_sensor) {
    device_address_sensor_ = device_address_sensor;
  }
  void set_light_control_on_voltage_sensor(sensor::Sensor *light_control_on_voltage_sensor) {
    light_control_on_voltage_sensor_ = light_control_on_voltage_sensor;
  }
  void set_light_control_off_voltage_sensor(sensor::Sensor *light_control_off_voltage_sensor) {
    light_control_off_voltage_sensor_ = light_control_off_voltage_sensor;
  }
  void set_light_control_on_period_1_sensor(sensor::Sensor *light_control_on_period_1_sensor) {
    light_control_on_period_1_sensor_ = light_control_on_period_1_sensor;
  }
  void set_light_control_on_period_2_sensor(sensor::Sensor *light_control_on_period_2_sensor) {
    light_control_on_period_2_sensor_ = light_control_on_period_2_sensor;
  }
  void set_load_turn_off_time_sensor(sensor::Sensor *load_turn_off_time_sensor) {
    load_turn_off_time_sensor_ = load_turn_off_time_sensor;
  }

  void set_battery_overvoltage_number(number::Number *battery_overvoltage_number) {
    battery_overvoltage_number_ = battery_overvoltage_number;
  }
  void set_charging_limit_voltage_number(number::Number *charging_limit_voltage_number) {
    charging_limit_voltage_number_ = charging_limit_voltage_number;
  }
  void set_battery_overvoltage_recovery_number(number::Number *battery_overvoltage_recovery_number) {
    battery_overvoltage_recovery_number_ = battery_overvoltage_recovery_number;
  }
  void set_equalizing_charging_voltage_number(number::Number *equalizing_charging_voltage_number) {
    equalizing_charging_voltage_number_ = equalizing_charging_voltage_number;
  }
  void set_boost_charging_voltage_number(number::Number *boost_charging_voltage_number) {
    boost_charging_voltage_number_ = boost_charging_voltage_number;
  }
  void set_boost_charging_return_voltage_number(number::Number *boost_charging_return_voltage_number) {
    boost_charging_return_voltage_number_ = boost_charging_return_voltage_number;
  }
  void set_floating_charge_voltage_number(number::Number *floating_charge_voltage_number) {
    floating_charge_voltage_number_ = floating_charge_voltage_number;
  }
  void set_over_discharge_voltage_number(number::Number *over_discharge_voltage_number) {
    over_discharge_voltage_number_ = over_discharge_voltage_number;
  }
  void set_over_discharge_recovery_voltage_number(number::Number *over_discharge_recovery_voltage_number) {
    over_discharge_recovery_voltage_number_ = over_discharge_recovery_voltage_number;
  }
  void set_battery_undervoltage_number(number::Number *battery_undervoltage_number) {
    battery_undervoltage_number_ = battery_undervoltage_number;
  }
  void set_equalization_charging_time_number(number::Number *equalization_charging_time_number) {
    equalization_charging_time_number_ = equalization_charging_time_number;
  }
  void set_improve_charging_time_number(number::Number *improve_charging_time_number) {
    improve_charging_time_number_ = improve_charging_time_number;
  }
  void set_temperature_compensation_coefficient_number(number::Number *temperature_compensation_coefficient_number) {
    temperature_compensation_coefficient_number_ = temperature_compensation_coefficient_number;
  }
  void set_device_address_number(number::Number *device_address_number) {
    device_address_number_ = device_address_number;
  }
  void set_light_control_on_voltage_number(number::Number *light_control_on_voltage_number) {
    light_control_on_voltage_number_ = light_control_on_voltage_number;
  }
  void set_light_control_off_voltage_number(number::Number *light_control_off_voltage_number) {
    light_control_off_voltage_number_ = light_control_off_voltage_number;
  }
  void set_light_control_on_period_1_number(number::Number *light_control_on_period_1_number) {
    light_control_on_period_1_number_ = light_control_on_period_1_number;
  }
  void set_light_control_on_period_2_number(number::Number *light_control_on_period_2_number) {
    light_control_on_period_2_number_ = light_control_on_period_2_number;
  }
  void set_load_turn_off_time_number(number::Number *load_turn_off_time_number) {
    load_turn_off_time_number_ = load_turn_off_time_number;
  }
  void set_battery_strings_number(number::Number *battery_strings_number) {
    battery_strings_number_ = battery_strings_number;
  }

  void set_operation_mode_text_sensor(text_sensor::TextSensor *operation_mode_text_sensor) {
    operation_mode_text_sensor_ = operation_mode_text_sensor;
  }
  void set_errors_text_sensor(text_sensor::TextSensor *errors_text_sensor) { errors_text_sensor_ = errors_text_sensor; }
  void set_battery_type_text_sensor(text_sensor::TextSensor *battery_type_text_sensor) {
    battery_type_text_sensor_ = battery_type_text_sensor;
  }

  void set_buzzer_switch(switch_::Switch *buzzer_switch) { buzzer_switch_ = buzzer_switch; }
  void set_street_light_mode_switch(switch_::Switch *street_light_mode_switch) {
    street_light_mode_switch_ = street_light_mode_switch;
  }
  void set_charging_switch(switch_::Switch *charging_switch) { charging_switch_ = charging_switch; }
  void set_load_switch(switch_::Switch *load_switch) { load_switch_ = load_switch; }

  void set_suppress_battery_temperature_errors(bool suppress_battery_temperature_errors) {
    suppress_battery_temperature_errors_ = suppress_battery_temperature_errors;
  }

  void set_enable_fake_traffic(bool enable_fake_traffic) { enable_fake_traffic_ = enable_fake_traffic; }

  void dump_config() override;

  void on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  binary_sensor::BinarySensor *load_detected_binary_sensor_;
  binary_sensor::BinarySensor *fan_running_binary_sensor_;
  binary_sensor::BinarySensor *charging_binary_sensor_;
  binary_sensor::BinarySensor *load_binary_sensor_;

  // status
  sensor::Sensor *firmware_version_sensor_;
  sensor::Sensor *pv_voltage_sensor_;
  sensor::Sensor *battery_voltage_sensor_;
  sensor::Sensor *channel_a_current_sensor_;
  sensor::Sensor *channel_b_current_sensor_;
  sensor::Sensor *charging_current_sensor_;
  sensor::Sensor *charger_temperature_sensor_;
  sensor::Sensor *charging_power_sensor_;
  sensor::Sensor *discharge_power_sensor_;
  sensor::Sensor *battery_capacity_sensor_;
  sensor::Sensor *operation_mode_id_sensor_;
  sensor::Sensor *discharge_current_sensor_;
  sensor::Sensor *discharge_times_sensor_;
  sensor::Sensor *total_charging_energy_sensor_;
  sensor::Sensor *total_discharge_energy_sensor_;
  sensor::Sensor *battery_temperature_sensor_;
  sensor::Sensor *error_bitmask_sensor_;
  sensor::Sensor *controller_voltage_level_sensor_;
  sensor::Sensor *pv_standby_voltage_sensor_;
  sensor::Sensor *controller_current_level_sensor_;
  sensor::Sensor *battery_temperature_compensation_voltage_point_sensor_;
  sensor::Sensor *battery_strings_sensor_;

  // configuration
  sensor::Sensor *battery_overvoltage_sensor_;
  sensor::Sensor *charging_limit_voltage_sensor_;
  sensor::Sensor *battery_overvoltage_recovery_sensor_;
  sensor::Sensor *equalizing_charging_voltage_sensor_;
  sensor::Sensor *boost_charging_voltage_sensor_;
  sensor::Sensor *boost_charging_return_voltage_sensor_;
  sensor::Sensor *floating_charge_voltage_sensor_;
  sensor::Sensor *over_discharge_voltage_sensor_;
  sensor::Sensor *over_discharge_recovery_voltage_sensor_;
  sensor::Sensor *battery_undervoltage_sensor_;
  sensor::Sensor *equalization_charging_time_sensor_;
  sensor::Sensor *improve_charging_time_sensor_;
  sensor::Sensor *temperature_compensation_coefficient_sensor_;
  sensor::Sensor *device_address_sensor_;
  sensor::Sensor *light_control_on_voltage_sensor_;
  sensor::Sensor *light_control_off_voltage_sensor_;
  sensor::Sensor *light_control_on_period_1_sensor_;
  sensor::Sensor *light_control_on_period_2_sensor_;
  sensor::Sensor *load_turn_off_time_sensor_;

  number::Number *battery_overvoltage_number_;
  number::Number *charging_limit_voltage_number_;
  number::Number *battery_overvoltage_recovery_number_;
  number::Number *equalizing_charging_voltage_number_;
  number::Number *boost_charging_voltage_number_;
  number::Number *boost_charging_return_voltage_number_;
  number::Number *floating_charge_voltage_number_;
  number::Number *over_discharge_voltage_number_;
  number::Number *over_discharge_recovery_voltage_number_;
  number::Number *battery_undervoltage_number_;
  number::Number *equalization_charging_time_number_;
  number::Number *improve_charging_time_number_;
  number::Number *temperature_compensation_coefficient_number_;
  number::Number *device_address_number_;
  number::Number *light_control_on_voltage_number_;
  number::Number *light_control_off_voltage_number_;
  number::Number *light_control_on_period_1_number_;
  number::Number *light_control_on_period_2_number_;
  number::Number *load_turn_off_time_number_;
  number::Number *battery_strings_number_;

  switch_::Switch *buzzer_switch_;
  switch_::Switch *street_light_mode_switch_;
  switch_::Switch *charging_switch_;
  switch_::Switch *load_switch_;

  text_sensor::TextSensor *operation_mode_text_sensor_;
  text_sensor::TextSensor *errors_text_sensor_;
  text_sensor::TextSensor *battery_type_text_sensor_;

  bool enable_fake_traffic_;
  bool suppress_battery_temperature_errors_;

  void on_status_data_(const std::vector<uint8_t> &data);
  void on_configuration_data_(const std::vector<uint8_t> &data);
  void on_write_data_(const std::vector<uint8_t> &data);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_state_(number::Number *number, float value);
  std::string error_bits_to_string_(uint16_t bitmask);
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
