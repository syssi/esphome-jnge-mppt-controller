#pragma once

#include "../jnge_wind_solar_controller.h"
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace jnge_wind_solar_controller {

class JngeWindSolarController;
class JngeSwitch : public switch_::Switch, public Component {
 public:
  void set_parent(JngeWindSolarController *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void write_state(bool state) override;
  JngeWindSolarController *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_wind_solar_controller
}  // namespace esphome
