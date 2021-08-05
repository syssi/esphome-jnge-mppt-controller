#include "jnge_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace jnge_mppt_controller {

static const char *const TAG = "jnge_mppt_controller.switch";

void JngeSwitch::dump_config() { LOG_SWITCH("", "Jnge_MpptController Switch", this); }
void JngeSwitch::write_state(bool state) { this->parent_->write_register(this->holding_register_, (uint16_t) state); }

}  // namespace jnge_mppt_controller
}  // namespace esphome
