import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_BATTERY_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    ICON_COUNTER,
    ICON_EMPTY,
    ICON_PERCENT,
    ICON_TIMELAPSE,
    ICON_TIMER,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_CELSIUS,
    UNIT_EMPTY,
    UNIT_PERCENT,
    UNIT_VOLT,
    UNIT_WATT,
)

from . import CONF_JNGE_MPPT_CONTROLLER_ID, JngeMpptController

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

CONF_FIRMWARE_VERSION = "firmware_version"
CONF_PV_VOLTAGE = "pv_voltage"
CONF_CHANNEL_A_CURRENT = "channel_a_current"
CONF_CHANNEL_B_CURRENT = "channel_b_current"
CONF_CHARGING_CURRENT = "charging_current"
CONF_CHARGER_TEMPERATURE = "charger_temperature"
CONF_CHARGING_POWER = "charging_power"
CONF_DISCHARGE_POWER = "discharge_power"
CONF_BATTERY_CAPACITY = "battery_capacity"
CONF_OPERATION_MODE_ID = "operation_mode_id"
CONF_DISCHARGE_CURRENT = "discharge_current"
CONF_DISCHARGE_TIMES = "discharge_times"
CONF_TOTAL_CHARGING_ENERGY = "total_charging_energy"
CONF_TOTAL_DISCHARGE_ENERGY = "total_discharge_energy"
CONF_BATTERY_TEMPERATURE = "battery_temperature"
CONF_ERROR_BITMASK = "error_bitmask"
CONF_CONTROLLER_VOLTAGE_LEVEL = "controller_voltage_level"
CONF_PV_STANDBY_VOLTAGE = "pv_standby_voltage"
CONF_CONTROLLER_CURRENT_LEVEL = "controller_current_level"
CONF_BATTERY_TEMPERATURE_COMPENSATION_VOLTAGE_POINT = (
    "battery_temperature_compensation_voltage_point"
)

CONF_BATTERY_OVERVOLTAGE = "battery_overvoltage"
CONF_CHARGING_LIMIT_VOLTAGE = "charging_limit_voltage"
CONF_BATTERY_OVERVOLTAGE_RECOVERY = "battery_overvoltage_recovery"
CONF_EQUALIZING_CHARGING_VOLTAGE = "equalizing_charging_voltage"
CONF_BOOST_CHARGING_VOLTAGE = "boost_charging_voltage"
CONF_BOOST_CHARGING_RETURN_VOLTAGE = "boost_charging_return_voltage"
CONF_FLOATING_CHARGE_VOLTAGE = "floating_charge_voltage"
CONF_OVER_DISCHARGE_VOLTAGE = "over_discharge_voltage"
CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE = "over_discharge_recovery_voltage"
CONF_BATTERY_UNDERVOLTAGE = "battery_undervoltage"
CONF_EQUALIZATION_CHARGING_TIME = "equalization_charging_time"
CONF_IMPROVE_CHARGING_TIME = "improve_charging_time"
CONF_TEMPERATURE_COMPENSATION_COEFFICIENT = "temperature_compensation_coefficient"
CONF_DEVICE_ADDRESS = "device_address"
CONF_LIGHT_CONTROL_ON_VOLTAGE = "light_control_on_voltage"
CONF_LIGHT_CONTROL_OFF_VOLTAGE = "light_control_off_voltage"
CONF_LIGHT_CONTROL_ON_PERIOD_1 = "light_control_on_period_1"
CONF_LIGHT_CONTROL_ON_PERIOD_2 = "light_control_on_period_2"
CONF_LOAD_TURN_OFF_TIME = "load_turn_off_time"
CONF_BATTERY_STRINGS = "battery_strings"

SENSORS = [
    # status
    CONF_FIRMWARE_VERSION,
    CONF_PV_VOLTAGE,
    CONF_BATTERY_VOLTAGE,
    CONF_CHANNEL_A_CURRENT,
    CONF_CHANNEL_B_CURRENT,
    CONF_CHARGING_CURRENT,
    CONF_CHARGER_TEMPERATURE,
    CONF_CHARGING_POWER,
    CONF_DISCHARGE_POWER,
    CONF_BATTERY_CAPACITY,
    CONF_OPERATION_MODE_ID,
    CONF_DISCHARGE_CURRENT,
    CONF_DISCHARGE_TIMES,
    CONF_TOTAL_CHARGING_ENERGY,
    CONF_TOTAL_DISCHARGE_ENERGY,
    CONF_BATTERY_TEMPERATURE,
    CONF_ERROR_BITMASK,
    CONF_CONTROLLER_VOLTAGE_LEVEL,
    CONF_PV_STANDBY_VOLTAGE,
    CONF_CONTROLLER_CURRENT_LEVEL,
    CONF_BATTERY_TEMPERATURE_COMPENSATION_VOLTAGE_POINT,
    # configuration
    CONF_BATTERY_OVERVOLTAGE,
    CONF_CHARGING_LIMIT_VOLTAGE,
    CONF_BATTERY_OVERVOLTAGE_RECOVERY,
    CONF_EQUALIZING_CHARGING_VOLTAGE,
    CONF_BOOST_CHARGING_VOLTAGE,
    CONF_BOOST_CHARGING_RETURN_VOLTAGE,
    CONF_FLOATING_CHARGE_VOLTAGE,
    CONF_OVER_DISCHARGE_VOLTAGE,
    CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE,
    CONF_BATTERY_UNDERVOLTAGE,
    CONF_EQUALIZATION_CHARGING_TIME,
    CONF_IMPROVE_CHARGING_TIME,
    CONF_TEMPERATURE_COMPENSATION_COEFFICIENT,
    CONF_DEVICE_ADDRESS,
    CONF_LIGHT_CONTROL_ON_VOLTAGE,
    CONF_LIGHT_CONTROL_OFF_VOLTAGE,
    CONF_LIGHT_CONTROL_ON_PERIOD_1,
    CONF_LIGHT_CONTROL_ON_PERIOD_2,
    CONF_LOAD_TURN_OFF_TIME,
    CONF_BATTERY_STRINGS,
]

ICON_ERROR_BITMASK = "mdi:alert-circle-outline"
ICON_BATTERY_STRINGS = "mdi:car-battery"
ICON_DEVICE_ADDRESS = "mdi:identifier"
ICON_TEMPERATURE_COMPENSATION_COEFFICIENT = "mdi:thermometer-plus"
ICON_OPERATION_MODE = "mdi:heart-pulse"
ICON_DISCHARGE_TIMES = "mdi:counter"

UNIT_HOURS = "h"
UNIT_KILO_WATT_HOURS = "kWh"
UNIT_MILLIVOLT = "mV"
UNIT_MILLIVOLT_PER_CELSIUS = "mV/°C"

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_MPPT_CONTROLLER_ID): cv.use_id(JngeMpptController),
        # status
        cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHANNEL_A_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHANNEL_B_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHARGING_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHARGER_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHARGING_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_DISCHARGE_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_CAPACITY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_PERCENT,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OPERATION_MODE_ID): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_OPERATION_MODE,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_DISCHARGE_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_DISCHARGE_TIMES): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_DISCHARGE_TIMES,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TOTAL_CHARGING_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_KILO_WATT_HOURS,
            icon=ICON_COUNTER,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_ENERGY,
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),
        cv.Optional(CONF_TOTAL_DISCHARGE_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_KILO_WATT_HOURS,
            icon=ICON_COUNTER,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_ENERGY,
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),
        cv.Optional(CONF_BATTERY_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_ERROR_BITMASK): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_ERROR_BITMASK,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CONTROLLER_VOLTAGE_LEVEL): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_STANDBY_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CONTROLLER_CURRENT_LEVEL): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(
            CONF_BATTERY_TEMPERATURE_COMPENSATION_VOLTAGE_POINT
        ): sensor.sensor_schema(
            unit_of_measurement=UNIT_MILLIVOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        # Configuration
        cv.Optional(CONF_BATTERY_OVERVOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CHARGING_LIMIT_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_OVERVOLTAGE_RECOVERY): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_EQUALIZING_CHARGING_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BOOST_CHARGING_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BOOST_CHARGING_RETURN_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FLOATING_CHARGE_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OVER_DISCHARGE_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_UNDERVOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_EQUALIZATION_CHARGING_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_HOURS,
            icon=ICON_TIMELAPSE,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_IMPROVE_CHARGING_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_HOURS,
            icon=ICON_TIMELAPSE,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TEMPERATURE_COMPENSATION_COEFFICIENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_MILLIVOLT_PER_CELSIUS,  # 0~6 mV/°C/2V
            icon=ICON_TEMPERATURE_COMPENSATION_COEFFICIENT,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_DEVICE_ADDRESS): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_DEVICE_ADDRESS,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LIGHT_CONTROL_OFF_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_PERIOD_1): sensor.sensor_schema(
            unit_of_measurement=UNIT_HOURS,
            icon=ICON_TIMER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_PERIOD_2): sensor.sensor_schema(
            unit_of_measurement=UNIT_HOURS,
            icon=ICON_TIMER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LOAD_TURN_OFF_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_HOURS,
            icon=ICON_TIMER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_STRINGS): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_BATTERY_STRINGS,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


def to_code(config):
    hub = yield cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = yield sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
