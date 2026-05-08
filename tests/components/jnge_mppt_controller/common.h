#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/jnge_mppt_controller/jnge_mppt_controller.h"

namespace esphome::jnge_mppt_controller::testing {

class TestableMpptController : public JngeMpptController {
 public:
  TestableMpptController() {
    suppress_battery_temperature_errors_ = false;
    enable_fake_traffic_ = false;
  }
  using JngeMpptController::on_status_data_;
  using JngeMpptController::on_configuration_data_;
};

}  // namespace esphome::jnge_mppt_controller::testing
