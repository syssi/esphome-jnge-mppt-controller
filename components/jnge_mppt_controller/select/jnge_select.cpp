#include "jnge_select.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jnge_mppt_controller {

static const char *const TAG = "jnge_mppt_controller.select";

void JngeSelect::dump_config() {
  LOG_SELECT(TAG, "JngeMpptController Select", this);
  ESP_LOGCONFIG(TAG, "  Select has register %u", this->holding_register_);
  ESP_LOGCONFIG(TAG, "  Options are:");
  auto options = this->traits.get_options();
  for (auto i = 0; i < this->mappings_.size(); i++) {
    ESP_LOGCONFIG(TAG, "    %i: %s", this->mappings_.at(i), options.at(i).c_str());
  }
}

void JngeSelect::control(const std::string &value) {
  auto idx = this->index_of(value);
  if (idx.has_value()) {
    uint8_t mapping = this->mappings_.at(idx.value());
    ESP_LOGV(TAG, "Setting %u datapoint value to %u:%s", this->holding_register_, mapping, value.c_str());
    this->parent_->write_register(this->holding_register_, mapping);
    return;
  }

  ESP_LOGW(TAG, "Invalid value %s", value.c_str());
}

}  // namespace jnge_mppt_controller
}  // namespace esphome
