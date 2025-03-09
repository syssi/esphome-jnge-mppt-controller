#include "jnge_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jnge_g_series {

static const char *const TAG = "jnge_g_series.number";

void JngeNumber::control(float value) {
  this->parent_->write_register(this->holding_register_, (uint16_t) (value * (1 / this->traits.get_step())));
}
void JngeNumber::dump_config() { LOG_NUMBER(TAG, "JngeGSeries Number", this); }

}  // namespace jnge_g_series
}  // namespace esphome
