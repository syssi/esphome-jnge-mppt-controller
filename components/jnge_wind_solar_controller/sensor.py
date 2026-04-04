import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_BATTERY_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_VOLTAGE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_COUNTER,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_EMPTY,
    UNIT_KILOWATT_HOURS,
    UNIT_VOLT,
    UNIT_WATT,
)

from . import JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

CONF_FIRMWARE_VERSION = "firmware_version"
CONF_PV_VOLTAGE = "pv_voltage"
CONF_FAN_VOLTAGE = "fan_voltage"
# CONF_BATTERY_VOLTAGE = "battery_voltage"
CONF_PV_CHARGING_CURRENT = "pv_charging_current"
CONF_FAN_CHARGING_CURRENT = "fan_charging_current"
CONF_PV_CHARGING_POWER = "pv_charging_power"
CONF_FAN_CHARGING_POWER = "fan_charging_power"
CONF_PV_TOTAL_ENERGY = "pv_total_energy"
CONF_FAN_TOTAL_ENERGY = "fan_total_energy"
CONF_OPERATION_MODE_ID = "operation_mode_id"
CONF_BATTERY_STRINGS = "battery_strings"
CONF_BATTERY_VOLTAGE_LEVEL = "battery_voltage_level"
CONF_ERROR_BITMASK = "error_bitmask"
CONF_PEAK_PV_CHARGING_RATING = "peak_pv_charging_rating"
CONF_PEAK_FAN_CHARGING_RATING = "peak_fan_charging_rating"

ICON_ERROR_BITMASK = "mdi:alert-circle-outline"
ICON_BATTERY_STRINGS = "mdi:car-battery"
ICON_DEVICE_ADDRESS = "mdi:identifier"
ICON_TEMPERATURE_COMPENSATION_COEFFICIENT = "mdi:thermometer-plus"
ICON_OPERATION_MODE = "mdi:heart-pulse"
ICON_DISCHARGE_TIMES = "mdi:counter"

UNIT_HOURS = "h"
UNIT_MILLIVOLT = "mV"
UNIT_MILLIVOLT_PER_CELSIUS = "mV/°C"

# key: sensor_schema kwargs
SENSOR_DEFS = {
    # status
    CONF_FIRMWARE_VERSION: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PEAK_PV_CHARGING_RATING: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PEAK_FAN_CHARGING_RATING: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PV_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_FAN_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_BATTERY_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PV_CHARGING_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_FAN_CHARGING_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PV_CHARGING_POWER: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_FAN_CHARGING_POWER: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_PV_TOTAL_ENERGY: {
        "unit_of_measurement": UNIT_KILOWATT_HOURS,
        "icon": ICON_COUNTER,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_ENERGY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
    },
    CONF_FAN_TOTAL_ENERGY: {
        "unit_of_measurement": UNIT_KILOWATT_HOURS,
        "icon": ICON_COUNTER,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_ENERGY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
    },
    CONF_OPERATION_MODE_ID: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_OPERATION_MODE,
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
    CONF_BATTERY_VOLTAGE_LEVEL: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_ERROR_BITMASK: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": ICON_ERROR_BITMASK,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
}

CONFIG_SCHEMA = JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): sensor.sensor_schema(**kwargs)
        for key, kwargs in SENSOR_DEFS.items()
    }
)


async def to_code(config):
    from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID

    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
