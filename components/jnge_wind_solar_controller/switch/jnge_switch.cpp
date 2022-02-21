#include "jnge_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace jnge_wind_solar_controller {

static const char *const TAG = "jnge_wind_solar_controller.switch";

void JngeSwitch::dump_config() { LOG_SWITCH("", "JngeWindSolarController Switch", this); }
void JngeSwitch::write_state(bool state) { this->parent_->write_register(this->holding_register_, (uint16_t) state); }

}  // namespace jnge_wind_solar_controller
}  // namespace esphome
