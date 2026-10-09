#include "jnge_number.h"
#include "esphome/core/log.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::jnge_mppt_controller {

ESPHOME_LOG_TAG(TAG, "jnge_mppt_controller.number");

void JngeNumber::control(float value) {
  this->parent_->write_register(this->holding_register_, (uint16_t) (value * (1 / this->traits.get_step())));
}
void JngeNumber::dump_config() { LOG_NUMBER(TAG, "JngeMpptController Number", this); }

}  // namespace esphome::jnge_mppt_controller
