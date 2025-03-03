#pragma once

#include "../jnge_g_series.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace jnge_g_series {

class JngeGSeries;

class JngeNumber : public number::Number, public Component {
 public:
  void set_parent(JngeGSeries *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;

 protected:
  void control(float value) override;

  JngeGSeries *parent_;
  uint16_t holding_register_;
};

}  // namespace jnge_g_series
}  // namespace esphome
