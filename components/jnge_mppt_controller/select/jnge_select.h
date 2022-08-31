#pragma once

#include <utility>
#include <map>

#include "../jnge_mppt_controller.h"
#include "esphome/components/select/select.h"
#include "esphome/core/component.h"

namespace esphome {
namespace jnge_mppt_controller {

class JngeMpptController;

class JngeSelect : public Component, public select::Select {
 public:
  void set_parent(JngeMpptController *const parent) { this->parent_ = parent; }
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void set_select_mappings(std::vector<uint16_t> mappings) { this->mappings_ = std::move(mappings); }

  void setup() override;
  void dump_config() override;

 protected:
  void control(const std::string &value) override;

  std::vector<uint16_t> mappings_;
  JngeMpptController *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
