#include "jnge_select.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jnge_mppt_controller {

static const char *const TAG = "jnge_mppt_controller.select";

void JngeSelect::dump_config() {
  LOG_SELECT(TAG, "JngeMpptController Select", this);
  ESP_LOGCONFIG(TAG, "  Options are:");
  for (auto const &map : this->mapping_) {
    ESP_LOGCONFIG(TAG, "    %s: %d", map.first.c_str(), map.second);
  }
}

void JngeSelect::map_and_publish(uint16_t &value) {
  ESP_LOGD(TAG, "Got value: %d", value);

  for (auto const &map : this->mapping_) {
    if (map.second == value) {
      ESP_LOGD(TAG, "Found mapped option %s of value %d", map.first.c_str(), value);
      this->publish_state(map.first);
      return;
    }
  }

  ESP_LOGD(TAG, "Could not find value %d in mapping", value);
}

void JngeSelect::control(const std::string &value) {
  ESP_LOGD(TAG, "Got option: %s", value.c_str());
  if (this->mapping_.find(value) != this->mapping_.end()) {
    ESP_LOGD(TAG, "Found mapped value %d of option %s", this->mapping_[value], value.c_str());
    this->parent_->write_register(this->holding_register_, this->mapping_[value]);
  } else {
    ESP_LOGD(TAG, "Could not find option %s in mapping", value.c_str());
    return;
  }
}

}  // namespace jnge_mppt_controller
}  // namespace esphome
