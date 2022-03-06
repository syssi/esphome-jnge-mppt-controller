#include "jnge_output.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace jnge_mppt_controller {

static const char *const TAG = "jnge_mppt_controller.output";

void JngeOutput::write_state(float state) {
  //  char tmp[10];
  //  sprintf(tmp, this->set_command_.c_str(), state);

  if (std::find(this->possible_values_.begin(), this->possible_values_.end(), state) != this->possible_values_.end()) {
    ESP_LOGD(TAG, "Will write: out of value %f / %02.0f", state, state);
    //    this->parent_->switch_command(std::string(tmp));
  } else {
    ESP_LOGD(TAG, "Will not write: as it is not in list of allowed values");
  }
}
}  // namespace jnge_mppt_controller
}  // namespace esphome
