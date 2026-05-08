#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/jnge_g_series/jnge_g_series.h"

namespace esphome::jnge_g_series::testing {

class TestableGSeries : public JngeGSeries {
 public:
  using JngeGSeries::on_status_data_;
};

}  // namespace esphome::jnge_g_series::testing
