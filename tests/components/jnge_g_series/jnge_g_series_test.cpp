#include <gtest/gtest.h>
#include "esphome/components/sensor/sensor.h"
#include "common.h"
#include "frames.h"

namespace esphome::jnge_g_series::testing {

class JngeGSeriesStatusTest : public ::testing::Test {
 protected:
  TestableGSeries inverter_;
  sensor::Sensor ac_voltage1_;
  sensor::Sensor ac_voltage2_;
  sensor::Sensor ac_frequency_;
  sensor::Sensor ac_current_;
  sensor::Sensor battery_voltage_;
  sensor::Sensor inverter_temperature_;
  sensor::Sensor total_energy_;
  sensor::Sensor ac_output_load_;
  sensor::Sensor ac_output_power_;

  void SetUp() override {
    inverter_.set_ac_voltage1_sensor(&ac_voltage1_);
    inverter_.set_ac_voltage2_sensor(&ac_voltage2_);
    inverter_.set_ac_frequency_sensor(&ac_frequency_);
    inverter_.set_ac_current_sensor(&ac_current_);
    inverter_.set_battery_voltage_sensor(&battery_voltage_);
    inverter_.set_inverter_temperature_sensor(&inverter_temperature_);
    inverter_.set_total_energy_sensor(&total_energy_);
    inverter_.set_ac_output_load_sensor(&ac_output_load_);
    inverter_.set_ac_output_power_sensor(&ac_output_power_);
  }
};

TEST_F(JngeGSeriesStatusTest, AcVoltage1) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_voltage1_.state, 229.7f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, AcVoltage2) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_voltage2_.state, 230.9f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, AcFrequency) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_frequency_.state, 49.99f, 0.005f);
}

TEST_F(JngeGSeriesStatusTest, AcCurrent) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_current_.state, 0.82f, 0.005f);
}

TEST_F(JngeGSeriesStatusTest, BatteryVoltage) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(battery_voltage_.state, 13.4f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, InverterTemperature) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(inverter_temperature_.state, 20.5f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, TotalEnergy) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(total_energy_.state, 337.7f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, AcOutputLoad) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_output_load_.state, 18.8f, 0.05f);
}

TEST_F(JngeGSeriesStatusTest, AcOutputPowerComputed) {
  inverter_.on_status_data_(G_SERIES_STATUS_FRAME);
  EXPECT_NEAR(ac_output_power_.state, 229.7f * 0.82f, 0.1f);
}

TEST_F(JngeGSeriesStatusTest, NullSensorSafe) {
  TestableGSeries bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_status_data_(G_SERIES_STATUS_FRAME));
}

}  // namespace esphome::jnge_g_series::testing
