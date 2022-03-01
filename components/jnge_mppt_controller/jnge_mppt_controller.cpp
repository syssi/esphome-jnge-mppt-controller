#include "jnge_mppt_controller.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace jnge_mppt_controller {

static const char *const TAG = "jnge_mppt_controller";

static const uint8_t READ_HOLDING_REGISTERS = 0x03;
static const uint8_t READ_INPUT_REGISTERS = 0x04;
static const uint8_t WRITE_SINGLE_REGISTER = 0x06;

static const uint8_t ERRORS_SIZE = 16;
static const char *const ERRORS[ERRORS_SIZE] = {
    "Battery overpressure",      // Byte 0.0, error
    "Battery is not connected",  // Byte 0.1, error
    "PV array overvoltage",      // Byte 0.2, error
    "Controller short circuit",  // Byte 0.3, error
    "Charging overcurrent",      // Byte 0.4, error
    "Controller overheated",     // Byte 0.5, error
    "Battery overheated",        // Byte 0.6, error
    "Output overload",           // Byte 0.7, error

    "Memory read/write error",                // Byte 1.0, error
    "Reserved",                               // Byte 1.1, error
    "Reserved",                               // Byte 1.2, error
    "Battery undervoltage",                   // Byte 1.3, warning
    "Controller temperature sensor failure",  // Byte 1.4, warning
    "Battery temperature sensor failure",     // Byte 1.5, warning
    "PV array undervoltage",                  // Byte 1.6, warning
    "Reserved",                               // Byte 1.7, warning
};

static const uint8_t OPERATION_MODES_SIZE = 5;
static const char *const OPERATION_MODES[OPERATION_MODES_SIZE] = {
    "Not charging",       // 0x00
    "MPPT charging",      // 0x01
    "Boost charging",     // 0x02
    "Float charging",     // 0x03
    "Equalizing charge",  // 0x04
};

static const uint8_t BATTERY_TYPES_SIZE = 5;
static const char *const BATTERY_TYPES[BATTERY_TYPES_SIZE] = {
    "Lead-Acid",        // 0x00
    "Gel",              // 0x01
    "Ternary Lithium",  // 0x02
    "LiFePo4",          // 0x03
    "Custom",           // 0x04
};

static const uint8_t CONTROLLER_VOLTAGE_LEVELS_SIZE = 14;
static const uint16_t CONTROLLER_VOLTAGE_LEVELS[CONTROLLER_VOLTAGE_LEVELS_SIZE] = {
    12,   // 0x00
    24,   // 0x01
    48,   // 0x02
    96,   // 0x03
    110,  // 0x04
    120,  // 0x05
    192,  // 0x06
    216,  // 0x07
    220,  // 0x08
    240,  // 0x09
    360,  // 0x0A
    384,  // 0x0B
    480,  // 0x0C
    540,  // 0x0D
};

static const uint8_t CONTROLLER_CURRENT_LEVELS_SIZE = 17;
static const uint16_t CONTROLLER_CURRENT_LEVELS[CONTROLLER_CURRENT_LEVELS_SIZE] = {
    3,    // 0x00
    5,    // 0x01
    10,   // 0x02
    15,   // 0x03
    20,   // 0x04
    30,   // 0x05
    40,   // 0x06
    50,   // 0x07
    60,   // 0x08
    70,   // 0x09
    80,   // 0x0A
    100,  // 0x0B
    120,  // 0x0C
    150,  // 0x0D
    200,  // 0x0E
    250,  // 0x0F
    300,  // 0x10
};

void JngeMpptController::on_jnge_modbus_data(const uint8_t &function, const std::vector<uint8_t> &data) {
  if (function == READ_INPUT_REGISTERS && data.size() == 58) {
    this->on_status_data_(data);

    // The controller cannot handle two commands in series. The configuration
    // request is send here to decouple the requests.
    //
    // Request device configuration -> 0x06 0x03 0x10 0x24 0x00 0x19 0xC1 0x7C
    this->send(READ_HOLDING_REGISTERS, 0x1024, 25);

    return;
  }

  if (function == READ_HOLDING_REGISTERS && data.size() == 50) {
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

  ESP_LOGW(TAG, "Invalid size (%zu) for JNGE MPPT Controller frame!", data.size());
}

void JngeMpptController::on_status_data_(const std::vector<uint8_t> &data) {
  auto jnge_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };
  auto jnge_get_32bit = [&](size_t i) -> uint32_t {
    return (uint32_t(jnge_get_16bit(i + 0)) << 16) | (uint32_t(jnge_get_16bit(i + 2)) << 0);
  };

  // Status request
  // -> 0x06 0x04 0x10 0x00 0x00 0x0D 0x35 0x74
  //    ^^^^ ^^^^ ^^^^^^^^^ ^^^^^^^^^ ^^^^^^^^^
  //    addr func    start    stop       crc
  //
  // Status response
  // <- 0x06 0x04 0x3A 0x00 0x04 0x00 0x00 0x00 0x78 0x00 0x00 0x00 0x00 0x00 0x00 0x00
  //    ^^^^ ^^^^ ^^^^ ^^^^^^^^^^^^....
  //    addr func dataLen data (0x3A = 58 bytes)
  //                     1    2    3    4    5    6    7    8    9   10   11   12   13
  //
  //    0x0C 0x00 0x00 0x00 0x00 0x00 0x28 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00
  //     14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29
  //
  //    0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x60 0x00 0x00 0x00 0x00 0x6E 0x00
  //     30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
  //
  //    0x06 0x00 0x01 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x01 0x6E 0xF0
  //     46   47   48   49   50   51   52   53   54   55   56  57   58   ^^^^^^^^^
  //                                                                       crc16
  //
  //
  // *readonly registers*
  //
  // Address Content                   Length    Coeff.  Unit      Example value
  //
  // 0x1000: Software version number    2 bytes
  this->publish_state_(this->firmware_version_sensor_, (float) jnge_get_16bit(0));

  // 0x1001: PV panel voltage           2 bytes  0.1      V
  this->publish_state_(this->pv_voltage_sensor_, (float) jnge_get_16bit(2) * 0.1f);  // V

  // 0x1002: Battery voltage            2 bytes  0.1      V
  this->publish_state_(this->battery_voltage_sensor_, (float) jnge_get_16bit(4) * 0.1f);  // V

  // 0x1003: A channel current          2 bytes  0.1      A
  this->publish_state_(this->channel_a_current_sensor_, (float) jnge_get_16bit(6) * 0.1f);  // A

  // 0x1004: B channel current          2 bytes  0.1      A
  this->publish_state_(this->channel_b_current_sensor_, (float) jnge_get_16bit(8) * 0.1f);  // A

  // 0x1005: Total charging current     2 bytes  0.1      A
  this->publish_state_(this->charging_current_sensor_, (float) jnge_get_16bit(10) * 0.1f);  // A

  // 0x1006: Charger temperature        2 bytes    1      °C
  this->publish_state_(this->charger_temperature_sensor_, (float) jnge_get_16bit(12));  // °C

  // 0x1007: Charging power             2 bytes  0.1      W
  this->publish_state_(this->charging_power_sensor_, (float) jnge_get_16bit(14) * 0.1f);  // W

  // 0x1008: Discharge power            2 bytes  0.1      W
  this->publish_state_(this->discharge_power_sensor_, (float) jnge_get_16bit(16) * 0.1f);  // W

  // 0x1009: Battery capacity           2 bytes    1      %
  this->publish_state_(this->battery_capacity_sensor_, (float) jnge_get_16bit(18));  // %

  // 0x100A: Operation mode             2 bytes                  00 (Not charging), 01 (MPPT charging),
  //                                                             02 (Boost charging), 03 (Float charging),
  //                                                             04 (Equalizing charge)
  uint16_t raw_operation_mode = jnge_get_16bit(20);
  this->publish_state_(this->operation_mode_id_sensor_, (float) raw_operation_mode);
  if (raw_operation_mode < OPERATION_MODES_SIZE) {
    this->publish_state_(this->operation_mode_text_sensor_, OPERATION_MODES[raw_operation_mode]);
  } else {
    this->publish_state_(this->operation_mode_text_sensor_, "Unknown");
  }

  // 0x100B: Load status                2 bytes                  00 (Disconnected), 01 (With load)
  this->publish_state_(this->load_detected_binary_sensor_, (bool) (jnge_get_16bit(22) == 0x01));

  // 0x100C: Discharge current          2 bytes  0.1      A
  this->publish_state_(this->discharge_current_sensor_, (float) jnge_get_16bit(24) * 0.1f);  // %

  // 0x100D: Over-discharge times       2 bytes    1
  this->publish_state_(this->discharge_times_sensor_, (float) jnge_get_16bit(26));

  // 0x100E: High total charging Wh     2 bytes  0.1      kWh
  // 0x100F: Low total charging Wh      2 bytes  0.1      kWh
  this->publish_state_(this->total_charging_energy_sensor_, (float) jnge_get_32bit(28) * 0.1f);

  // 0x1010: High total discharge Wh    2 bytes  0.1      kWh
  // 0x1011: Low total discharge Wh     2 bytes  0.1      kWh
  this->publish_state_(this->total_discharge_energy_sensor_, (float) jnge_get_32bit(32) * 0.1f);

  // 0x1012: Battery temperature        2 bytes    1      °C
  this->publish_state_(this->battery_temperature_sensor_, (float) jnge_get_16bit(36));

  // 0x1013: Error code bitmask         2 bytes                  see (1) Error code bits
  uint16_t raw_error_bitmask = jnge_get_16bit(38);

  if (this->suppress_battery_temperature_errors_) {
    raw_error_bitmask &= ~(1 << 13);
  }

  this->publish_state_(this->error_bitmask_sensor_, (float) raw_error_bitmask);
  this->publish_state_(this->errors_text_sensor_, this->error_bits_to_string_(raw_error_bitmask));

  // 0x1014: Controller voltage level   2 bytes                  0 (12V system), 1 (24V system), 2 (48V system),
  //                                                             3 (96V), 4 (110V), 5 (120V), 6 (192V), 7 (216V),
  //                                                             8 (220V), 9 (240V), 10 (360V), 11 (384V),
  //                                                             12 (480V), 13 (540V)
  uint16_t raw_controller_voltage_level = jnge_get_16bit(40);
  float controller_voltage_level = 0.0f;
  if (raw_controller_voltage_level < CONTROLLER_VOLTAGE_LEVELS_SIZE) {
    controller_voltage_level = CONTROLLER_VOLTAGE_LEVELS[raw_controller_voltage_level];
  }
  this->publish_state_(this->controller_voltage_level_sensor_, controller_voltage_level);

  // 0x1015: PV Standby voltage         2 bytes  0.1      V
  this->publish_state_(this->pv_standby_voltage_sensor_, (float) jnge_get_16bit(42) * 0.1f);

  // 0x1016: Controller current level   2 bytes                  0 (3A), 1 (5A), 2 (10A), 3 (15A), 4 (20A),
  //                                                             5 (30A), 6 (40A), 7 (50A), 8 (60A), 9 (70A),
  //                                                             10 (80A), 11 (100A), 12 (120A), 13 (150A),
  //                                                             14 (200A), 15 (250A), 16 (300A)
  uint16_t raw_controller_current_level = jnge_get_16bit(44);
  float controller_current_level = 0.0f;
  if (raw_controller_current_level < CONTROLLER_CURRENT_LEVELS_SIZE) {
    controller_current_level = CONTROLLER_CURRENT_LEVELS[raw_controller_current_level];
  }
  this->publish_state_(this->controller_current_level_sensor_, controller_current_level);

  // 0x1017: Number of battery strings  2 bytes    1
  this->publish_state_(this->battery_strings_sensor_, (float) jnge_get_16bit(46));

  // 0x1018: Battery type               2 bytes                  0 (Lead-Acid), 1 (Gel), 2 (Ternary Lithium),
  //                                                             3 (LiFePo4), 4 (Custom)
  uint16_t raw_battery_type = jnge_get_16bit(48);
  if (raw_battery_type < BATTERY_TYPES_SIZE) {
    this->publish_state_(this->battery_type_text_sensor_, BATTERY_TYPES[raw_battery_type]);
  } else {
    this->publish_state_(this->battery_type_text_sensor_, "Unknown");
  }

  // 0x1019: Charging switch status     2 bytes                  0 (Charging off), 1 (Charging on)
  this->publish_state_(this->charging_binary_sensor_, (bool) (jnge_get_16bit(50) == 0x01));

  // 0x101A: Fan status                 2 bytes                  0 (Idle), 1 (Running)
  this->publish_state_(this->fan_running_binary_sensor_, (bool) (jnge_get_16bit(52) == 0x01));

  // 0x101B: Battery temperature composenation voltage point  2 bytes    1  mV
  this->publish_state_(this->battery_temperature_compensation_voltage_point_sensor_, (float) jnge_get_16bit(54));

  // 0x101C: Load switch status         2 bytes                  0 (Load off), 1 (Load on)
  this->publish_state_(this->load_binary_sensor_, (bool) (jnge_get_16bit(56) == 0x01));

  // ----> 29 register * 2 bytes = 58 bytes data
  //
  // ... (reserved)
  // 0x1023: (reserved)
  //
  // (1) Error code bits
  //
  // 0: Battery overpressure                    error
  // 1: Battery is not connected                error
  // 2: PV array overvoltage                    error
  // 3: Controller short circuit                error
  // 4: Charging overcurrent                    error
  // 5: Controller overheated                   error
  // 6: Battery overheated                      error
  // 7: Output overload                         error
  // 8: Memory read/write error                 error
  // 9: Reserved                                error
  // 10: Reserved                               error
  // 11: Battery undervoltage                   warning
  // 12: Controller temperature sensor failure  warning
  // 13: Battery temperature sensor failure     warning
  // 14: PV array undervoltage                  warning
  // 15: Reserved                               warning
}

void JngeMpptController::on_configuration_data_(const std::vector<uint8_t> &data) {
  auto jnge_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  // Configuration request
  // -> 0x06 0x03 0x10 0x24 0x00 0x19 0xC1 0x7C
  //    ^^^^ ^^^^ ^^^^^^^^^ ^^^^^^^^^ ^^^^^^^^^
  //    addr func    start    stop       crc
  //
  // Status response
  // <- 0x06 0x04 0x3A 0x00 0x04 0x00 0x00 0x00 0x78 0x00 0x00 0x00 0x00 0x00 0x00 0x00
  //    ^^^^ ^^^^ ^^^^ ^^^^^^^^^^^^....
  //    addr func dataLen data (0x3A = 58 bytes)
  //                     1    2    3    4    5    6    7    8    9   10   11   12   13
  //
  //    0x0C 0x00 0x00 0x00 0x00 0x00 0x28 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00
  //     14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29
  //
  //    0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x60 0x00 0x00 0x00 0x00 0x6E 0x00
  //     30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
  //
  //    0x06 0x00 0x01 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x01 0x6E 0xF0
  //     46   47   48   49   50   51   52   53   54   55   56  57   58   ^^^^^^^^^
  //                                                                       crc16
  //
  //
  // *read/write registers*
  //
  // Address Content                          Length    Coeff.  Unit     Example value
  //
  // 0x1024: Overvoltage                      2 bytes   0.1     V
  this->publish_state_(this->overvoltage_sensor_, (float) jnge_get_16bit(0) * 0.1f);

  // 0x1025: Charging limit voltage           2 bytes   0.1     V
  this->publish_state_(this->charging_limit_voltage_sensor_, (float) jnge_get_16bit(2) * 0.1f);

  // 0x1026: Overvoltage recovery             2 bytes   0.1     V
  this->publish_state_(this->overvoltage_recovery_sensor_, (float) jnge_get_16bit(4) * 0.1f);

  // 0x1027: Equalizing charging voltage      2 bytes   0.1     V
  this->publish_state_(this->equalizing_charging_voltage_sensor_, (float) jnge_get_16bit(6) * 0.1f);

  // 0x1028: Boost charging voltage           2 bytes   0.1     V
  this->publish_state_(this->boost_charging_voltage_sensor_, (float) jnge_get_16bit(8) * 0.1f);

  // 0x1029: Boost charging return voltage    2 bytes   0.1     V
  this->publish_state_(this->boost_charging_return_voltage_sensor_, (float) jnge_get_16bit(10) * 0.1f);

  // 0x102A: Floating charge voltage          2 bytes   0.1     V
  this->publish_state_(this->floating_charge_voltage_sensor_, (float) jnge_get_16bit(12) * 0.1f);

  // 0x102B: Over discharge voltage           2 bytes   0.1     V
  this->publish_state_(this->over_discharge_voltage_sensor_, (float) jnge_get_16bit(14) * 0.1f);

  // 0x102C: Over discharge recovery voltage  2 bytes   0.1     V
  this->publish_state_(this->over_discharge_recovery_voltage_sensor_, (float) jnge_get_16bit(16) * 0.1f);

  // 0x102D: Battery undervoltage             2 bytes   0.1     V
  this->publish_state_(this->undervoltage_sensor_, (float) jnge_get_16bit(18) * 0.1f);

  // 0x102E: Equalization charging time       2 bytes     1     H         1~3 H
  this->publish_state_(this->equalization_charging_time_sensor_, (float) jnge_get_16bit(20));

  // 0x102F: Improve charging time            2 bytes     1     H         1~3 H
  this->publish_state_(this->improve_charging_time_sensor_, (float) jnge_get_16bit(22));

  // 0x1030: Temperature compensation coefficient  2 bytes                0~6 mV/°C/2V
  this->publish_state_(this->temperature_compensation_coefficient_sensor_, (float) jnge_get_16bit(24));

  // 0x1031: Device address                   2 bytes                     1~255
  this->publish_state_(this->device_address_sensor_, (float) jnge_get_16bit(26));

  // 0x1032: Light control on voltage         2 bytes   0.1     V         5~11V
  this->publish_state_(this->light_control_on_voltage_sensor_, (float) jnge_get_16bit(28) * 0.1f);

  // 0x1033: Light control off voltage        2 bytes   0.1     V         5~11V
  this->publish_state_(this->light_control_off_voltage_sensor_, (float) jnge_get_16bit(30) * 0.1f);

  // 0x1034: Light control on period 1        2 bytes     1     H
  this->publish_state_(this->light_control_on_period_1_sensor_, (float) jnge_get_16bit(32));

  // 0x1035: Light control on period 2        2 bytes     1     H
  this->publish_state_(this->light_control_on_period_2_sensor_, (float) jnge_get_16bit(34));

  // 0x1036: Household or street light mode   2 bytes                     0 (Household), 1 (Street light)
  this->publish_state_(this->street_light_mode_switch_, (bool) (jnge_get_16bit(36) == 0x01));

  // 0x1037: Turn the load off                2 bytes     1     H
  this->publish_state_(this->load_turn_off_time_sensor_, (float) jnge_get_16bit(38));

  // 0x1038: Charging on/off                  2 bytes                     0 (Charger off), 1 (Charger on)
  this->publish_state_(this->charging_switch_, (bool) (jnge_get_16bit(40) == 0x01));

  // 0x1039: Buzzer on/off                    2 bytes                     0 (Buzzer off), 1 (Buzzer on)
  this->publish_state_(this->buzzer_switch_, (bool) (jnge_get_16bit(42) == 0x01));

  // 0x103A: Number of battery strings        2 bytes
  // this->publish_state_(this->battery_strings_number_, (float) jnge_get_16bit(44));

  // 0x103B: Battery Type                     2 bytes                     0 (Lead-acid), 1 (gel), 2 (ternary lithium),
  //                                                                      3 (LiFePo4), 4 (Custom)
  // this->publish_state_(this->battery_type_control_sensor_, (float) jnge_get_16bit(46));

  // 0x103C: Load on/off                      2 bytes                     0 (Load off), 1 (Load on)
  this->publish_state_(this->load_switch_, (bool) (jnge_get_16bit(48) == 0x01));

  // ----> 25 register * 2 bytes = 50 bytes data
  //
  // 0x103D: (reserved)
  // 0x104D: (reserved)
  // ...
  // 0x104A: (reserved)
}

void JngeMpptController::on_write_data_(const std::vector<uint8_t> &data) {
  ESP_LOGI(TAG, "Write register response received: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void JngeMpptController::write_register(uint16_t address, uint16_t value) {
  // Example writer register request
  // this->write_register(0x1024, 157); -> 0x06 0x06 0x10 0x24 0x00 0x9D 0x0D 0x1F
  this->send(WRITE_SINGLE_REGISTER, address, value);

  ESP_LOGI(TAG, "Write register request: %02X.%02X.%02X.%02X (4)", (uint8_t)(address >> 8), (uint8_t) address,
           (uint8_t)(value >> 8), (uint8_t) value);
}

void JngeMpptController::update() {
  // Request device status -> 0x06 0x04 0x10 0x00 0x00 0x1D 0x35 0x74
  this->send(READ_INPUT_REGISTERS, 0x1000, 29);

  // Example status response
  //
  // this->on_jnge_modbus_data({0x00, 0x04, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //                            0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  //                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  //                            0x00, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  //                            0x00, 0x00, 0x00, 0x00, 0x00, 0x01});

  // Example configuration responses
  //
  // this->on_jnge_modbus_data({0x00, 0x9B, 0x00, 0x95, 0x00, 0x96, 0x00, 0x90, 0x00, 0x90, 0x00, 0x84, 0x00,
  //                            0x8A, 0x00, 0x6C, 0x00, 0x83, 0x00, 0x6C, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03,
  //                            0x00, 0x06, 0x00, 0x32, 0x00, 0x3C, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00,
  //                            0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01});
  //
  // this->on_jnge_modbus_data({0x00, 0x9B, 0x00, 0x95, 0x00, 0x96, 0x00, 0x90, 0x00, 0x90, 0x00, 0x84, 0x00,
  //                            0x8A, 0x00, 0x6C, 0x00, 0x83, 0x00, 0x6C, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03,
  //                            0x00, 0x06, 0x00, 0x32, 0x00, 0x3C, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00,
  //                            0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01});
}

void JngeMpptController::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;

  binary_sensor->publish_state(state);
}

void JngeMpptController::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void JngeMpptController::publish_state_(switch_::Switch *obj, const bool &state) {
  if (obj == nullptr)
    return;

  obj->publish_state(state);
}

void JngeMpptController::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;

  text_sensor->publish_state(state);
}

std::string JngeMpptController::error_bits_to_string_(const uint16_t mask) {
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

void JngeMpptController::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "JngeMpptController:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("", "Firmware Version", this->firmware_version_sensor_);
  LOG_SENSOR("", "PV Voltage", this->pv_voltage_sensor_);
  LOG_SENSOR("", "Battery Voltage", this->battery_voltage_sensor_);
  LOG_SENSOR("", "Channel A Current", this->channel_a_current_sensor_);
  LOG_SENSOR("", "Channel B Current", this->channel_b_current_sensor_);
  LOG_SENSOR("", "Charging Current", this->charging_current_sensor_);
  LOG_SENSOR("", "Charger Temperature", this->charger_temperature_sensor_);
  LOG_SENSOR("", "Charging Power", this->charging_power_sensor_);
  LOG_SENSOR("", "Discharge Power", this->discharge_power_sensor_);
  LOG_SENSOR("", "Battery Capacity", this->battery_capacity_sensor_);
  LOG_SENSOR("", "Operation Mode Id", this->operation_mode_id_sensor_);
  LOG_TEXT_SENSOR("", "Operation Mode", this->operation_mode_text_sensor_);
  LOG_SENSOR("", "Discharge Current", this->discharge_current_sensor_);
  LOG_SENSOR("", "Discharge Times", this->discharge_times_sensor_);
  LOG_SENSOR("", "Total Energy Charging", this->total_charging_energy_sensor_);
  LOG_SENSOR("", "Total Energy Discharge", this->total_discharge_energy_sensor_);
  LOG_SENSOR("", "Battery Temperature", this->battery_temperature_sensor_);
  LOG_SENSOR("", "Error bitmask", this->error_bitmask_sensor_);
  LOG_TEXT_SENSOR("", "Errors", this->errors_text_sensor_);
  LOG_SENSOR("", "Controller Voltage Level", this->controller_voltage_level_sensor_);
  LOG_SENSOR("", "PV Standby Voltage", this->pv_standby_voltage_sensor_);
  LOG_SENSOR("", "Controller Current Level", this->controller_current_level_sensor_);
  LOG_SENSOR("", "Battery Strings", this->battery_strings_sensor_);
  LOG_TEXT_SENSOR("", "Battery Type", this->battery_type_text_sensor_);
  LOG_BINARY_SENSOR("", "Charging", this->charging_binary_sensor_);
  LOG_BINARY_SENSOR("", "Fan Running", this->fan_running_binary_sensor_);
  LOG_SENSOR("", "Battery Temperature Compensation Voltage Point",
             this->battery_temperature_compensation_voltage_point_sensor_);

  LOG_SENSOR("", "Overvoltage", this->overvoltage_sensor_);
  LOG_SENSOR("", "Charging Voltage Limit", this->charging_limit_voltage_sensor_);
  LOG_SENSOR("", "Overvoltage Recovery", this->overvoltage_recovery_sensor_);
  LOG_SENSOR("", "Equalizing Charging Voltage", this->equalizing_charging_voltage_sensor_);
  LOG_SENSOR("", "Boost Charging Voltage", this->boost_charging_voltage_sensor_);
  LOG_SENSOR("", "Boost Charging Return Voltage", this->boost_charging_return_voltage_sensor_);
  LOG_SENSOR("", "Floating Charge Voltage", this->floating_charge_voltage_sensor_);
  LOG_SENSOR("", "Over Discharge Voltage", this->over_discharge_voltage_sensor_);
  LOG_SENSOR("", "Over Discharge Recovery Voltage", this->over_discharge_recovery_voltage_sensor_);
  LOG_SENSOR("", "Undervoltage", this->undervoltage_sensor_);
  LOG_SENSOR("", "Equalization Charging Time", this->equalization_charging_time_sensor_);
  LOG_SENSOR("", "Improve Charging Time", this->improve_charging_time_sensor_);
  LOG_SENSOR("", "Temperature Compensation Coefficient", this->temperature_compensation_coefficient_sensor_);
  LOG_SENSOR("", "Device Address", this->device_address_sensor_);
  LOG_SENSOR("", "Light Control On Voltage", this->light_control_on_voltage_sensor_);
  LOG_SENSOR("", "Light Control Off Voltage", this->light_control_off_voltage_sensor_);
  LOG_SENSOR("", "Light Control On Period 1", this->light_control_on_period_1_sensor_);
  LOG_SENSOR("", "Light Control On Period 2", this->light_control_on_period_2_sensor_);
  LOG_SENSOR("", "Load Turn Off Time", this->load_turn_off_time_sensor_);
  LOG_BINARY_SENSOR("", "Load", this->load_binary_sensor_);
}

}  // namespace jnge_mppt_controller
}  // namespace esphome
