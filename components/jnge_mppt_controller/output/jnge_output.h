#pragma once

#include "../jnge_mppt_controller.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"

namespace esphome {
namespace jnge_mppt_controller {

class JngeMpptController;

class JngeOutput : public output::FloatOutput {
 public:
  JngeOutput() {}
  void set_parent(JngeMpptController *parent) { this->parent_ = parent; }
  void set_set_command(const std::string &command) { this->set_command_ = command; };
  void set_possible_values(std::vector<float> possible_values) { this->possible_values_ = std::move(possible_values); }
  void set_value(float value) { this->write_state(value); };

 protected:
  void write_state(float state) override;
  std::string set_command_;
  JngeMpptController *parent_;
  std::vector<float> possible_values_;
};

template<typename... Ts> class SetOutputAction : public Action<Ts...> {
 public:
  SetOutputAction(JngeOutput *output) : output_(output) {}

  TEMPLATABLE_VALUE(float, level)

  void play(Ts... x) override { this->output_->set_value(this->level_.value(x...)); }

 protected:
  JngeOutput *output_;
};

}  // namespace jnge_mppt_controller
}  // namespace esphome
