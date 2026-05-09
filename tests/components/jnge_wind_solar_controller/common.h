#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/jnge_wind_solar_controller/jnge_wind_solar_controller.h"

namespace esphome::jnge_wind_solar_controller::testing {

class TestableWindSolarController : public JngeWindSolarController {
 public:
  TestableWindSolarController() { enable_fake_traffic_ = false; }
  using JngeWindSolarController::on_read_registers_data_;
};

}  // namespace esphome::jnge_wind_solar_controller::testing
