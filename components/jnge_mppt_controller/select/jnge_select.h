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
  void set_select_mappings(std::vector<uint8_t> mappings) { this->mappings_ = std::move(mappings); }

  void dump_config() override;
  void map_and_publish(uint16_t &value);
  void control(const std::string &value) override;

 protected:
  std::vector<uint8_t> mappings_;
  uint8_t select_id_;
  JngeMpptController *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
