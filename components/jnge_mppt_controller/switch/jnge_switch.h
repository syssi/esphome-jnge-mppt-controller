#pragma once

#include "../jnge_mppt_controller.h"
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace jnge_mppt_controller {

class JngeMpptController;
class JngeSwitch : public switch_::Switch, public Component {
 public:
  void set_parent(JngeMpptController *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void write_state(bool state) override;
  JngeMpptController *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
