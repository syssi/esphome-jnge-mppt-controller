#pragma once

#include <utility>

#include "../jnge_mppt_controller.h"
#include "esphome/components/select/select.h"
#include "esphome/core/component.h"

namespace esphome {
namespace jnge_mppt_controller {

class JngeSelect : public Component, public select::Select {
 public:
  void set_parent(JngeMpptController *const parent) { this->parent_ = parent; }
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void add_mapping(const std::string &key, const uint16_t &value) { this->mapping_[key] = value; }

  void dump_config() override;
  void map_and_publish(uint16_t &value);
  void control(const std::string &value) override;

 protected:
  std::map<std::string, uint16_t> mapping_;
  JngeMpptController *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
