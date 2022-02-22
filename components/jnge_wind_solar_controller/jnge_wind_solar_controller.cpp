#include "jnge_wind_solar_controller.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace jnge_wind_solar_controller {

static const char *const TAG = "jnge_wind_solar_controller";

static const uint8_t READ_REGISTERS = 0x03;
static const uint8_t WRITE_SINGLE_REGISTER = 0x06;

static const uint8_t ERRORS_SIZE = 16;
static const char *const ERRORS[ERRORS_SIZE] = {
    "PV charging overcurrent",          // Byte 0.0, error
    "Short circuit fault",              // Byte 0.1, error
    "",                                 // Byte 0.2, error
    "PV charging battery overvoltage",  // Byte 0.3, error
    "PV array overvoltage (reverse)",   // Byte 0.4, error
    "Fan input overvoltage",            // Byte 0.5, error
    "Fan charging overcurrent",         // Byte 0.6, error
    "",                                 // Byte 0.7, error

    "",                       // Byte 1.0, error
    "",                       // Byte 1.1, error
    "",                       // Byte 1.2, error
    "",                       // Byte 1.3, warning
    "Battery undervoltage",   // Byte 1.4, warning
    "",                       // Byte 1.5, warning
    "PV array undervoltage",  // Byte 1.6, warning
    "",                       // Byte 1.7, warning

};

static const uint8_t OPERATION_MODES_SIZE = 5;
static const char *const OPERATION_MODES[OPERATION_MODES_SIZE] = {
    "Not charging",               // 0x00
    "Constant-current charging",  // 0x01
    "Boost charging",             // 0x02
    "Float charging",             // 0x03
};

static const uint8_t BATTERY_TYPES_SIZE = 5;
static const char *const BATTERY_TYPES[BATTERY_TYPES_SIZE] = {
    "Unknown",          // 0x00
    "Lead-Acid",        // 0x01
    "LiFePo4",          // 0x02
    "Ternary Lithium",  // 0x03
    "Custom",           // 0x04
};

void JngeWindSolarController::on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) {
  if (function == READ_REGISTERS && data.size() == 38) {
    this->on_status_data_(data);

    // The controller cannot handle two commands in series. The configuration
    // request is send here to decouple the requests.
    //
    // Request device configuration -> 0x06 0x03 0x10 0x24 0x00 0x19 0xC1 0x7C
    this->send(READ_REGISTERS, 0x1024, 25);

    return;
  }

  if (function == READ_REGISTERS && data.size() == 50) {
    this->on_configuration_data_(data);

    return;
  }

  // -> 0x06 0x06 0x10 0x24 0x00 0x9D 0x0D 0x1F
  // <- 0x06 0x06 0x10 0x24 0x00 0x9D 0x0D 0x1F
  //    ^^^^ ^^^^ ^^^^^^^^^^^^^^^^^^^ ^^^^^^^^^
  //    addr func        data           crc16
  //
  // Success if the response is equal to the request
  if (function == WRITE_SINGLE_REGISTER && data.size() == 4) {
    this->on_write_data_(data);

    return;
  }

  ESP_LOGW(TAG, "Invalid size (%zu) for JNGE Solar and Wind Hybrid Controller frame!", data.size());
}

void JngeWindSolarController::on_status_data_(const std::vector<uint8_t> &data) {
  auto jnge_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };
  auto jnge_get_32bit = [&](size_t i) -> uint32_t {
    return (uint32_t(jnge_get_16bit(i + 0)) << 16) | (uint32_t(jnge_get_16bit(i + 2)) << 0);
  };

  // *readonly registers*
  //
  // Address: Field                     Length    Coeff.  Unit      Example value
  //
  // 0x1000: Battery voltage            2 bytes  0.1      V
  this->publish_state_(this->battery_voltage_sensor_, (float) jnge_get_16bit(0) * 0.1f);  // V
  // 0x1001: PV voltage                 2 bytes  0.1      V
  this->publish_state_(this->pv_voltage_sensor_, (float) jnge_get_16bit(2) * 0.1f);  // V
  // 0x1002: Fan voltage                2 bytes  0.1      V
  this->publish_state_(this->fan_voltage_sensor_, (float) jnge_get_16bit(4) * 0.1f);  // V
  // 0x1003: PV charging current        2 bytes  0.1      A
  this->publish_state_(this->pv_charging_current_sensor_, (float) jnge_get_16bit(6) * 0.1f);  // A
  // 0x1004: Fan charging current       2 bytes  0.1      A
  this->publish_state_(this->fan_charging_current_sensor_, (float) jnge_get_16bit(8) * 0.1f);  // A
  // 0x1005: PV charging power          2 bytes    1      W
  this->publish_state_(this->pv_charging_power_sensor_, (float) jnge_get_16bit(10));  // W
  // 0x1006: Fan charging power         2 bytes    1      W
  this->publish_state_(this->fan_charging_power_sensor_, (float) jnge_get_16bit(12));  // W
  // 0x1007: PV total energy            2 bytes  0.1      kWh
  this->publish_state_(this->pv_total_energy_sensor_, (float) jnge_get_32bit(14) * 0.1f);  // kWh
  // 0x1008: Fan total energy           2 bytes  0.1      kWh
  this->publish_state_(this->fan_total_energy_sensor_, (float) jnge_get_32bit(16) * 0.1f);  // kWh
  // 0x1009: Operation mode             2 bytes    1
  uint16_t raw_operation_mode = jnge_get_16bit(18);
  this->publish_state_(this->operation_mode_id_sensor_, (float) raw_operation_mode);
  if (raw_operation_mode < OPERATION_MODES_SIZE) {
    this->publish_state_(this->operation_mode_text_sensor_, OPERATION_MODES[raw_operation_mode]);
  } else {
    this->publish_state_(this->operation_mode_text_sensor_, "Unknown");
  }
  // 0x100A: Load status                2 bytes                  0 (Disconnected), 1 (With load)
  this->publish_state_(this->load_detected_binary_sensor_, (bool) (jnge_get_16bit(20) == 0x01));
  // 0x100B: Version number             2 bytes
  this->publish_state_(this->firmware_version_sensor_, (float) jnge_get_16bit(22));
  // 0x100C: PV charging rating         2 bytes  100      W (Ppv) -> can be changed via 0x1054. Software limit?
  this->publish_state_(this->peak_pv_charging_rating_sensor_, (float) data[24]);
  // 0x100D: Fan charging rating        2 bytes  100      W (Pfan) -> can be changed via 0x1055. Software limit?
  this->publish_state_(this->peak_fan_charging_rating_sensor_, (float) data[26]);
  // 0x100E: Number of battery strings  2 bytes    1      N
  this->publish_state_(this->battery_strings_sensor_, (float) jnge_get_16bit(28));
  // 0x100F: Battery type               2 bytes
  uint16_t raw_battery_type = jnge_get_16bit(30);
  if (raw_battery_type < BATTERY_TYPES_SIZE) {
    this->publish_state_(this->battery_type_text_sensor_, BATTERY_TYPES[raw_battery_type]);
  } else {
    this->publish_state_(this->battery_type_text_sensor_, "Unknown");
  }
  // 0x1010: Battery voltage level      2 bytes                  12V, 24V, 48V
  this->publish_state_(this->battery_voltage_level_sensor_, (float) jnge_get_16bit(32) * 0.1f);
  // 0x1011: Error code bitmask         2 bytes
  uint16_t raw_error_bitmask = jnge_get_16bit(34);
  this->publish_state_(this->error_bitmask_sensor_, (float) raw_error_bitmask);
  this->publish_state_(this->errors_text_sensor_, this->error_bits_to_string_(raw_error_bitmask));
  // 0x1012: PV charging switch         2 bytes                  0 (Charging off), 1 (Charging on)
  this->publish_state_(this->charging_binary_sensor_, (bool) (jnge_get_16bit(36) == 0x01));
  // 0x1013: Load switch machine        2 bytes                  0 (Off), 1 (On)
  this->publish_state_(this->load_binary_sensor_, (bool) (jnge_get_16bit(38) == 0x01));
  //
  // ----> 19 register * 2 bytes = 38 bytes data
}

void JngeWindSolarController::on_configuration_data_(const std::vector<uint8_t> &data) {
  // Not implemented yet
}

void JngeWindSolarController::on_write_data_(const std::vector<uint8_t> &data) {
  ESP_LOGI(TAG, "Write register response received: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void JngeWindSolarController::write_register(uint16_t address, uint16_t value) {
  // Example writer register request
  // this->write_register(0x1024, 157); -> 0x06 0x06 0x10 0x24 0x00 0x9D 0x0D 0x1F
  this->send(WRITE_SINGLE_REGISTER, address, value);

  ESP_LOGI(TAG, "Write register request: %02X.%02X.%02X.%02X (4)", (uint8_t)(address >> 8), (uint8_t) address,
           (uint8_t)(value >> 8), (uint8_t) value);
}

void JngeWindSolarController::update() {
  // Request device status -> 0x06 0x03 0x10 0x00 0x00 0x13 0x01 0x70
  this->send(READ_REGISTERS, 0x1000, 19);

  // Example status response
  //
  // Header: 0x06, 0x03, 0x26,
  /*
  this->on_jnge_modbus_data(READ_REGISTERS,
                            {0x00, 0x93, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00,
                             0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00,
                             0x04, 0x00, 0x01, 0x00, 0x04, 0x00, 0x78, 0x40, 0x00, 0x00, 0x01});
                             */
  // CRC: 0x29, 0x1B

  // Example configuration responses
  //
  // Header: 0x06, 0x03, 0x32,
  /*
  this->on_jnge_modbus_data(
      READ_REGISTERS,
      {0x00, 0x96, 0x00, 0x8C, 0x00, 0x92, 0x00, 0x8D, 0x00, 0x90, 0x00, 0x8B, 0x00, 0x6E, 0x00, 0x78,
       0x00, 0x01, 0x00, 0x78, 0x00, 0x04, 0x00, 0x01, 0x00, 0x06, 0x00, 0x3C, 0x00, 0x32, 0x00, 0x00, 0x00, 0x06, 0x00,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00});
       */
  // CRC: 0x93, 0x77
}

void JngeWindSolarController::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;

  binary_sensor->publish_state(state);
}

void JngeWindSolarController::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void JngeWindSolarController::publish_state_(switch_::Switch *obj, const bool &state) {
  if (obj == nullptr)
    return;

  obj->publish_state(state);
}

void JngeWindSolarController::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;

  text_sensor->publish_state(state);
}

std::string JngeWindSolarController::error_bits_to_string_(const uint16_t mask) {
  bool first = true;
  std::string errors_list = "";

  if (mask) {
    for (int i = 0; i < ERRORS_SIZE; i++) {
      if (mask & (1 << i)) {
        if (first) {
          first = false;
        } else {
          errors_list.append(";");
        }
        errors_list.append(ERRORS[i]);
      }
    }
  }

  return errors_list;
}

void JngeWindSolarController::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "JngeWindSolarController:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("", "Battery Voltage", this->battery_voltage_sensor_);
  LOG_SENSOR("", "PV Voltage", this->pv_voltage_sensor_);
  LOG_SENSOR("", "Fan Voltage", this->fan_voltage_sensor_);
  LOG_SENSOR("", "PV Charging Current", this->pv_charging_current_sensor_);
  LOG_SENSOR("", "Fan Charging Current", this->fan_charging_current_sensor_);
  LOG_SENSOR("", "PV Charging Power", this->pv_charging_power_sensor_);
  LOG_SENSOR("", "Fan Charging Power", this->fan_charging_power_sensor_);
  LOG_SENSOR("", "PV Total Energy", this->pv_total_energy_sensor_);
  LOG_SENSOR("", "Fan Total Energy", this->fan_total_energy_sensor_);
  LOG_SENSOR("", "Operation Mode Id", this->operation_mode_id_sensor_);
  LOG_TEXT_SENSOR("", "Operation Mode", this->operation_mode_text_sensor_);
  LOG_BINARY_SENSOR("", "Load detected", this->load_detected_binary_sensor_);
  LOG_SENSOR("", "Firmware Version", this->firmware_version_sensor_);
  LOG_SENSOR("", "Peak PV Charging Rating", this->peak_pv_charging_rating_sensor_);
  LOG_SENSOR("", "Peak Fan Charging Rating", this->peak_fan_charging_rating_sensor_);
  LOG_SENSOR("", "Battery Strings", this->battery_strings_sensor_);
  LOG_TEXT_SENSOR("", "Battery Type", this->battery_type_text_sensor_);
  LOG_SENSOR("", "Battery Voltage Level", this->battery_voltage_level_sensor_);
  LOG_SENSOR("", "Error bitmask", this->error_bitmask_sensor_);
  LOG_TEXT_SENSOR("", "Errors", this->errors_text_sensor_);
  LOG_BINARY_SENSOR("", "Charging", this->charging_binary_sensor_);
  LOG_BINARY_SENSOR("", "Load enabled", this->load_binary_sensor_);
}

}  // namespace jnge_wind_solar_controller
}  // namespace esphome
