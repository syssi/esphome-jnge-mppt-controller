#include <gtest/gtest.h>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "common.h"
#include "frames.h"

namespace esphome::jnge_wind_solar_controller::testing {

class JngeWindSolarStatusTest : public ::testing::Test {
 protected:
  TestableWindSolarController controller_;
  sensor::Sensor battery_voltage_;
  sensor::Sensor pv_voltage_;
  sensor::Sensor fan_voltage_;
  sensor::Sensor pv_charging_current_;
  sensor::Sensor fan_charging_current_;
  sensor::Sensor pv_charging_power_;
  sensor::Sensor fan_charging_power_;
  sensor::Sensor pv_total_energy_;
  sensor::Sensor fan_total_energy_;
  sensor::Sensor operation_mode_id_;
  sensor::Sensor firmware_version_;
  sensor::Sensor peak_pv_charging_rating_;
  sensor::Sensor peak_fan_charging_rating_;
  sensor::Sensor battery_strings_;
  sensor::Sensor battery_voltage_level_;
  sensor::Sensor error_bitmask_;
  binary_sensor::BinarySensor load_detected_;
  binary_sensor::BinarySensor charging_;
  binary_sensor::BinarySensor load_;
  text_sensor::TextSensor operation_mode_;
  text_sensor::TextSensor battery_type_;
  text_sensor::TextSensor errors_;

  void SetUp() override {
    controller_.set_battery_voltage_sensor(&battery_voltage_);
    controller_.set_pv_voltage_sensor(&pv_voltage_);
    controller_.set_fan_voltage_sensor(&fan_voltage_);
    controller_.set_pv_charging_current_sensor(&pv_charging_current_);
    controller_.set_fan_charging_current_sensor(&fan_charging_current_);
    controller_.set_pv_charging_power_sensor(&pv_charging_power_);
    controller_.set_fan_charging_power_sensor(&fan_charging_power_);
    controller_.set_pv_total_energy_sensor(&pv_total_energy_);
    controller_.set_fan_total_energy_sensor(&fan_total_energy_);
    controller_.set_operation_mode_id_sensor(&operation_mode_id_);
    controller_.set_firmware_version_sensor(&firmware_version_);
    controller_.set_peak_pv_charging_rating_sensor(&peak_pv_charging_rating_);
    controller_.set_peak_fan_charging_rating_sensor(&peak_fan_charging_rating_);
    controller_.set_battery_strings_sensor(&battery_strings_);
    controller_.set_battery_voltage_level_sensor(&battery_voltage_level_);
    controller_.set_error_bitmask_sensor(&error_bitmask_);
    controller_.set_load_detected_binary_sensor(&load_detected_);
    controller_.set_charging_binary_sensor(&charging_);
    controller_.set_load_binary_sensor(&load_);
    controller_.set_operation_mode_text_sensor(&operation_mode_);
    controller_.set_battery_type_text_sensor(&battery_type_);
    controller_.set_errors_text_sensor(&errors_);
  }
};

TEST_F(JngeWindSolarStatusTest, BatteryVoltage) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_NEAR(battery_voltage_.state, 12.4f, 0.05f);
}

TEST_F(JngeWindSolarStatusTest, PvVoltageZero) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_NEAR(pv_voltage_.state, 0.0f, 0.01f);
}

TEST_F(JngeWindSolarStatusTest, PvChargingPowerZero) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FLOAT_EQ(pv_charging_power_.state, 0.0f);
}

TEST_F(JngeWindSolarStatusTest, OperationModeNotCharging) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FLOAT_EQ(operation_mode_id_.state, 0.0f);
  EXPECT_EQ(operation_mode_.state, "Not charging");
}

TEST_F(JngeWindSolarStatusTest, LoadDetectedFalse) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FALSE(load_detected_.state);
}

TEST_F(JngeWindSolarStatusTest, FirmwareVersion) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FLOAT_EQ(firmware_version_.state, 2.0f);
}

TEST_F(JngeWindSolarStatusTest, BatteryStrings) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FLOAT_EQ(battery_strings_.state, 1.0f);
}

TEST_F(JngeWindSolarStatusTest, BatteryTypeCustom) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_EQ(battery_type_.state, "Custom");
}

TEST_F(JngeWindSolarStatusTest, BatteryVoltageLevel) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_NEAR(battery_voltage_level_.state, 12.0f, 0.05f);
}

TEST_F(JngeWindSolarStatusTest, ErrorBitmaskPvUndervoltage) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FLOAT_EQ(error_bitmask_.state, 0x4000);
  EXPECT_EQ(errors_.state, "PV array undervoltage");
}

TEST_F(JngeWindSolarStatusTest, ChargingTrue) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_TRUE(charging_.state);
}

TEST_F(JngeWindSolarStatusTest, LoadBinaryFalse) {
  controller_.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME);
  EXPECT_FALSE(load_.state);
}

TEST_F(JngeWindSolarStatusTest, NullSensorSafe) {
  TestableWindSolarController bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_read_registers_data_(WIND_SOLAR_STATUS_FRAME));
}

}  // namespace esphome::jnge_wind_solar_controller::testing
