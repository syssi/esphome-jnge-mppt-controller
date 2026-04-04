import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_BATTERY_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_FREQUENCY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_COUNTER,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_CELSIUS,
    UNIT_HERTZ,
    UNIT_KILOWATT_HOURS,
    UNIT_PERCENT,
    UNIT_VOLT,
    UNIT_WATT,
)

from . import CONF_JNGE_G_SERIES_ID, JNGE_G_SERIES_COMPONENT_SCHEMA

DEPENDENCIES = ["jnge_g_series"]

CODEOWNERS = ["@syssi"]

# CONF_BATTERY_VOLTAGE = "battery_voltage"
CONF_AC_VOLTAGE1 = "ac_voltage1"
CONF_AC_VOLTAGE2 = "ac_voltage2"
CONF_AC_FREQUENCY = "ac_frequency"
CONF_AC_CURRENT = "ac_current"
CONF_TOTAL_ENERGY = "total_energy"
CONF_INVERTER_TEMPERATURE = "inverter_temperature"
CONF_AC_OUTPUT_LOAD = "ac_output_load"
CONF_AC_OUTPUT_POWER = "ac_output_power"

# key: sensor_schema kwargs
SENSOR_DEFS = {
    CONF_BATTERY_VOLTAGE: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": "mdi:car-battery",
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_VOLTAGE1: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_VOLTAGE2: {
        "unit_of_measurement": UNIT_VOLT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_VOLTAGE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_FREQUENCY: {
        "unit_of_measurement": UNIT_HERTZ,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_FREQUENCY,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_TOTAL_ENERGY: {
        "unit_of_measurement": UNIT_KILOWATT_HOURS,
        "icon": ICON_COUNTER,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_ENERGY,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_INVERTER_TEMPERATURE: {
        "unit_of_measurement": UNIT_CELSIUS,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_OUTPUT_LOAD: {
        "unit_of_measurement": UNIT_PERCENT,
        "icon": "mdi:gauge",
        "accuracy_decimals": 1,
        "device_class": "power_factor",
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_AC_OUTPUT_POWER: {
        "unit_of_measurement": UNIT_WATT,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 1,
        "device_class": DEVICE_CLASS_POWER,
        "state_class": STATE_CLASS_MEASUREMENT,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
}

CONFIG_SCHEMA = JNGE_G_SERIES_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): sensor.sensor_schema(**kwargs)
        for key, kwargs in SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_G_SERIES_ID])
    for key in SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
