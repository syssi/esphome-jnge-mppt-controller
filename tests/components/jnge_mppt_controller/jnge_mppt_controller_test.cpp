#include <gtest/gtest.h>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "common.h"
#include "frames.h"

namespace esphome::jnge_mppt_controller::testing {

class JngeMpptStatusTest : public ::testing::Test {
 protected:
  TestableMpptController controller_;
  sensor::Sensor firmware_version_;
  sensor::Sensor pv_voltage_;
  sensor::Sensor battery_voltage_;
  sensor::Sensor channel_a_current_;
  sensor::Sensor channel_b_current_;
  sensor::Sensor charging_current_;
  sensor::Sensor charger_temperature_;
  sensor::Sensor charging_power_;
  sensor::Sensor discharge_power_;
  sensor::Sensor battery_capacity_;
  sensor::Sensor operation_mode_id_;
  sensor::Sensor discharge_current_;
  sensor::Sensor discharge_times_;
  sensor::Sensor total_charging_energy_;
  sensor::Sensor total_discharge_energy_;
  sensor::Sensor battery_temperature_;
  sensor::Sensor error_bitmask_;
  sensor::Sensor controller_voltage_level_;
  sensor::Sensor pv_standby_voltage_;
  sensor::Sensor controller_current_level_;
  sensor::Sensor battery_strings_;
  sensor::Sensor battery_temperature_compensation_voltage_point_;
  binary_sensor::BinarySensor load_detected_;
  binary_sensor::BinarySensor charging_;
  binary_sensor::BinarySensor fan_running_;
  binary_sensor::BinarySensor load_;
  text_sensor::TextSensor operation_mode_;
  text_sensor::TextSensor battery_type_;
  text_sensor::TextSensor errors_;

  void SetUp() override {
    controller_.set_firmware_version_sensor(&firmware_version_);
    controller_.set_pv_voltage_sensor(&pv_voltage_);
    controller_.set_battery_voltage_sensor(&battery_voltage_);
    controller_.set_channel_a_current_sensor(&channel_a_current_);
    controller_.set_channel_b_current_sensor(&channel_b_current_);
    controller_.set_charging_current_sensor(&charging_current_);
    controller_.set_charger_temperature_sensor(&charger_temperature_);
    controller_.set_charging_power_sensor(&charging_power_);
    controller_.set_discharge_power_sensor(&discharge_power_);
    controller_.set_battery_capacity_sensor(&battery_capacity_);
    controller_.set_operation_mode_id_sensor(&operation_mode_id_);
    controller_.set_discharge_current_sensor(&discharge_current_);
    controller_.set_discharge_times_sensor(&discharge_times_);
    controller_.set_total_charging_energy_sensor(&total_charging_energy_);
    controller_.set_total_discharge_energy_sensor(&total_discharge_energy_);
    controller_.set_battery_temperature_sensor(&battery_temperature_);
    controller_.set_error_bitmask_sensor(&error_bitmask_);
    controller_.set_controller_voltage_level_sensor(&controller_voltage_level_);
    controller_.set_pv_standby_voltage_sensor(&pv_standby_voltage_);
    controller_.set_controller_current_level_sensor(&controller_current_level_);
    controller_.set_battery_strings_sensor(&battery_strings_);
    controller_.set_battery_temperature_compensation_voltage_point_sensor(
        &battery_temperature_compensation_voltage_point_);
    controller_.set_load_detected_binary_sensor(&load_detected_);
    controller_.set_charging_binary_sensor(&charging_);
    controller_.set_fan_running_binary_sensor(&fan_running_);
    controller_.set_load_binary_sensor(&load_);
    controller_.set_operation_mode_text_sensor(&operation_mode_);
    controller_.set_battery_type_text_sensor(&battery_type_);
    controller_.set_errors_text_sensor(&errors_);
  }
};

TEST_F(JngeMpptStatusTest, FirmwareVersion) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(firmware_version_.state, 4.0f);
}

TEST_F(JngeMpptStatusTest, BatteryVoltage) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_NEAR(battery_voltage_.state, 12.0f, 0.01f);
}

TEST_F(JngeMpptStatusTest, PvVoltage) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_NEAR(pv_voltage_.state, 0.0f, 0.01f);
}

TEST_F(JngeMpptStatusTest, ChargingCurrentZero) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_NEAR(charging_current_.state, 0.0f, 0.001f);
}

TEST_F(JngeMpptStatusTest, ChargerTemperature) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(charger_temperature_.state, 12.0f);
}

TEST_F(JngeMpptStatusTest, BatteryCapacity) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(battery_capacity_.state, 40.0f);
}

TEST_F(JngeMpptStatusTest, OperationModeNotCharging) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(operation_mode_id_.state, 0.0f);
  EXPECT_EQ(operation_mode_.state, "Not charging");
}

TEST_F(JngeMpptStatusTest, LoadDetectedTrue) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_TRUE(load_detected_.state);
}

TEST_F(JngeMpptStatusTest, ErrorBitmask) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(error_bitmask_.state, 0x6000);
  EXPECT_EQ(errors_.state, "Battery temperature sensor failure;PV array undervoltage");
}

TEST_F(JngeMpptStatusTest, ControllerVoltageLevel12V) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(controller_voltage_level_.state, 12.0f);
}

TEST_F(JngeMpptStatusTest, PvStandbyVoltage) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_NEAR(pv_standby_voltage_.state, 11.0f, 0.01f);
}

TEST_F(JngeMpptStatusTest, ControllerCurrentLevel40A) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(controller_current_level_.state, 40.0f);
}

TEST_F(JngeMpptStatusTest, BatteryStrings) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FLOAT_EQ(battery_strings_.state, 1.0f);
}

TEST_F(JngeMpptStatusTest, BatteryTypeLeadAcid) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_EQ(battery_type_.state, "Lead Acid");
}

TEST_F(JngeMpptStatusTest, ChargingTrue) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_TRUE(charging_.state);
}

TEST_F(JngeMpptStatusTest, FanRunningFalse) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_FALSE(fan_running_.state);
}

TEST_F(JngeMpptStatusTest, LoadBinaryTrue) {
  controller_.on_status_data_(MPPT_STATUS_FRAME);
  EXPECT_TRUE(load_.state);
}

TEST_F(JngeMpptStatusTest, NullSensorSafe) {
  TestableMpptController bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_status_data_(MPPT_STATUS_FRAME));
}

class JngeMpptConfigTest : public ::testing::Test {
 protected:
  TestableMpptController controller_;
  sensor::Sensor battery_overvoltage_;
  sensor::Sensor charging_limit_voltage_;
  sensor::Sensor battery_overvoltage_recovery_;
  sensor::Sensor equalizing_charging_voltage_;
  sensor::Sensor boost_charging_voltage_;
  sensor::Sensor boost_charging_return_voltage_;
  sensor::Sensor floating_charge_voltage_;
  sensor::Sensor over_discharge_voltage_;
  sensor::Sensor over_discharge_recovery_voltage_;
  sensor::Sensor battery_undervoltage_;
  sensor::Sensor equalization_charging_time_;
  sensor::Sensor improve_charging_time_;
  sensor::Sensor temperature_compensation_coefficient_;
  sensor::Sensor device_address_;
  sensor::Sensor light_control_on_voltage_;
  sensor::Sensor light_control_off_voltage_;
  sensor::Sensor light_control_on_period_1_;
  sensor::Sensor light_control_on_period_2_;
  sensor::Sensor load_turn_off_time_;

  void SetUp() override {
    controller_.set_battery_overvoltage_sensor(&battery_overvoltage_);
    controller_.set_charging_limit_voltage_sensor(&charging_limit_voltage_);
    controller_.set_battery_overvoltage_recovery_sensor(&battery_overvoltage_recovery_);
    controller_.set_equalizing_charging_voltage_sensor(&equalizing_charging_voltage_);
    controller_.set_boost_charging_voltage_sensor(&boost_charging_voltage_);
    controller_.set_boost_charging_return_voltage_sensor(&boost_charging_return_voltage_);
    controller_.set_floating_charge_voltage_sensor(&floating_charge_voltage_);
    controller_.set_over_discharge_voltage_sensor(&over_discharge_voltage_);
    controller_.set_over_discharge_recovery_voltage_sensor(&over_discharge_recovery_voltage_);
    controller_.set_battery_undervoltage_sensor(&battery_undervoltage_);
    controller_.set_equalization_charging_time_sensor(&equalization_charging_time_);
    controller_.set_improve_charging_time_sensor(&improve_charging_time_);
    controller_.set_temperature_compensation_coefficient_sensor(&temperature_compensation_coefficient_);
    controller_.set_device_address_sensor(&device_address_);
    controller_.set_light_control_on_voltage_sensor(&light_control_on_voltage_);
    controller_.set_light_control_off_voltage_sensor(&light_control_off_voltage_);
    controller_.set_light_control_on_period_1_sensor(&light_control_on_period_1_);
    controller_.set_light_control_on_period_2_sensor(&light_control_on_period_2_);
    controller_.set_load_turn_off_time_sensor(&load_turn_off_time_);
  }
};

TEST_F(JngeMpptConfigTest, BatteryOvervoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(battery_overvoltage_.state, 15.5f, 0.01f);
}

TEST_F(JngeMpptConfigTest, ChargingLimitVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(charging_limit_voltage_.state, 14.9f, 0.01f);
}

TEST_F(JngeMpptConfigTest, BoostChargingVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(boost_charging_voltage_.state, 14.4f, 0.01f);
}

TEST_F(JngeMpptConfigTest, FloatingChargeVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(floating_charge_voltage_.state, 13.8f, 0.01f);
}

TEST_F(JngeMpptConfigTest, OverDischargeVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(over_discharge_voltage_.state, 10.8f, 0.01f);
}

TEST_F(JngeMpptConfigTest, BatteryUndervoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(battery_undervoltage_.state, 10.8f, 0.01f);
}

TEST_F(JngeMpptConfigTest, EqualizationChargingTime) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_FLOAT_EQ(equalization_charging_time_.state, 2.0f);
}

TEST_F(JngeMpptConfigTest, ImproveChargingTime) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_FLOAT_EQ(improve_charging_time_.state, 1.0f);
}

TEST_F(JngeMpptConfigTest, DeviceAddress) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_FLOAT_EQ(device_address_.state, 6.0f);
}

TEST_F(JngeMpptConfigTest, LightControlOnVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(light_control_on_voltage_.state, 5.0f, 0.01f);
}

TEST_F(JngeMpptConfigTest, LightControlOffVoltage) {
  controller_.on_configuration_data_(MPPT_CONFIG_FRAME);
  EXPECT_NEAR(light_control_off_voltage_.state, 6.0f, 0.01f);
}

TEST_F(JngeMpptConfigTest, NullSensorSafe) {
  TestableMpptController bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_configuration_data_(MPPT_CONFIG_FRAME));
}

}  // namespace esphome::jnge_mppt_controller::testing
