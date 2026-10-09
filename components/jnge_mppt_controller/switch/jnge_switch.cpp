#include "jnge_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::jnge_mppt_controller {

ESPHOME_LOG_TAG(TAG, "jnge_mppt_controller.switch");

void JngeSwitch::dump_config() { LOG_SWITCH("", "JngeMpptController Switch", this); }
void JngeSwitch::write_state(bool state) { this->parent_->write_register(this->holding_register_, (uint16_t) state); }

}  // namespace esphome::jnge_mppt_controller
