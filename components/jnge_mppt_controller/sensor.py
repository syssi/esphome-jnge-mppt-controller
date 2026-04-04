import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_BATTERY_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    ENTITY_CATEGORY_DIAGNOSTIC,
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
    UNIT_KILOWATT_HOURS,
    UNIT_PERCENT,
    UNIT_VOLT,
    UNIT_WATT,
)

from . import (
    CONF_JNGE_MPPT_CONTROLLER_ID,
    JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA,
    UNIT_HOURS,
)

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

ICON_ERROR_BITMASK = "mdi:alert-circle-outline"
ICON_BATTERY_STRINGS = "mdi:car-battery"
ICON_DEVICE_ADDRESS = "mdi:identifier"
ICON_TEMPERATURE_COMPENSATION_COEFFICIENT = "mdi:thermometer-plus"
ICON_OPERATION_MODE = "mdi:heart-pulse"
ICON_DISCHARGE_TIMES = "mdi:counter"

UNIT_MILLIVOLT = "mV"
UNIT_MILLIVOLT_PER_CELSIUS = "mV/°C"

SENSOR_DEFS = {
    # status
    CONF_FIRMWARE_VERSION: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_PV_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_BATTERY_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHANNEL_A_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHANNEL_B_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHARGING_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHARGER_TEMPERATURE: {
        "unit_of_measurement": UNIT_CELSIUS,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHARGING_POWER: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_DISCHARGE_POWER: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_BATTERY_CAPACITY: {
        "unit_of_measurement": UNIT_PERCENT,
        "icon": ICON_PERCENT,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_OPERATION_MODE_ID: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_OPERATION_MODE,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_DISCHARGE_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_DISCHARGE_TIMES: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_DISCHARGE_TIMES,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_TOTAL_CHARGING_ENERGY: {
        "unit_of_measurement": UNIT_KILOWATT_HOURS,
        "icon": ICON_COUNTER,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_ENERGY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_TOTAL_DISCHARGE_ENERGY: {
        "unit_of_measurement": UNIT_KILOWATT_HOURS,
        "icon": ICON_COUNTER,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_ENERGY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_BATTERY_TEMPERATURE: {
        "unit_of_measurement": UNIT_CELSIUS,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_ERROR_BITMASK: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_ERROR_BITMASK,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CONTROLLER_VOLTAGE_LEVEL: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_PV_STANDBY_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CONTROLLER_CURRENT_LEVEL: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_BATTERY_TEMPERATURE_COMPENSATION_VOLTAGE_POINT: {
        "unit_of_measurement": UNIT_MILLIVOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    # Configuration
    CONF_BATTERY_OVERVOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_CHARGING_LIMIT_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BATTERY_OVERVOLTAGE_RECOVERY: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_EQUALIZING_CHARGING_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BOOST_CHARGING_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BOOST_CHARGING_RETURN_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_FLOATING_CHARGE_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_OVER_DISCHARGE_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BATTERY_UNDERVOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_EQUALIZATION_CHARGING_TIME: {
        "unit_of_measurement": UNIT_HOURS,
        "icon": ICON_TIMELAPSE,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_IMPROVE_CHARGING_TIME: {
        "unit_of_measurement": UNIT_HOURS,
        "icon": ICON_TIMELAPSE,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_TEMPERATURE_COMPENSATION_COEFFICIENT: {
        "unit_of_measurement": UNIT_MILLIVOLT_PER_CELSIUS,  # 0~6 mV/°C/2V
        "icon": ICON_TEMPERATURE_COMPENSATION_COEFFICIENT,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_DEVICE_ADDRESS: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_DEVICE_ADDRESS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LIGHT_CONTROL_ON_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LIGHT_CONTROL_OFF_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LIGHT_CONTROL_ON_PERIOD_1: {
        "unit_of_measurement": UNIT_HOURS,
        "icon": ICON_TIMER,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LIGHT_CONTROL_ON_PERIOD_2: {
        "unit_of_measurement": UNIT_HOURS,
        "icon": ICON_TIMER,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LOAD_TURN_OFF_TIME: {
        "unit_of_measurement": UNIT_HOURS,
        "icon": ICON_TIMER,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BATTERY_STRINGS: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_BATTERY_STRINGS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
}

CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): sensor.sensor_schema(**kwargs)
        for key, kwargs in SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key in SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
