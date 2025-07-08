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

SENSORS = [
    CONF_FIRMWARE_VERSION,
    CONF_PEAK_PV_CHARGING_RATING,
    CONF_PEAK_FAN_CHARGING_RATING,
    CONF_PV_VOLTAGE,
    CONF_FAN_VOLTAGE,
    CONF_BATTERY_VOLTAGE,
    CONF_PV_CHARGING_CURRENT,
    CONF_FAN_CHARGING_CURRENT,
    CONF_PV_CHARGING_POWER,
    CONF_FAN_CHARGING_POWER,
    CONF_PV_TOTAL_ENERGY,
    CONF_FAN_TOTAL_ENERGY,
    CONF_OPERATION_MODE_ID,
    CONF_BATTERY_STRINGS,
    CONF_BATTERY_VOLTAGE_LEVEL,
    CONF_ERROR_BITMASK,
]

ICON_ERROR_BITMASK = "mdi:alert-circle-outline"
ICON_BATTERY_STRINGS = "mdi:car-battery"
ICON_DEVICE_ADDRESS = "mdi:identifier"
ICON_TEMPERATURE_COMPENSATION_COEFFICIENT = "mdi:thermometer-plus"
ICON_OPERATION_MODE = "mdi:heart-pulse"
ICON_DISCHARGE_TIMES = "mdi:counter"

UNIT_HOURS = "h"
UNIT_MILLIVOLT = "mV"
UNIT_MILLIVOLT_PER_CELSIUS = "mV/°C"

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        # status
        cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PEAK_PV_CHARGING_RATING): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PEAK_FAN_CHARGING_RATING): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FAN_VOLTAGE): sensor.sensor_schema(
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
        cv.Optional(CONF_PV_CHARGING_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FAN_CHARGING_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_CHARGING_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FAN_CHARGING_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_TOTAL_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_KILOWATT_HOURS,
            icon=ICON_COUNTER,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_ENERGY,
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),
        cv.Optional(CONF_FAN_TOTAL_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_KILOWATT_HOURS,
            icon=ICON_COUNTER,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_ENERGY,
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),
        cv.Optional(CONF_OPERATION_MODE_ID): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_OPERATION_MODE,
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
        cv.Optional(CONF_BATTERY_VOLTAGE_LEVEL): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_ERROR_BITMASK): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_ERROR_BITMASK,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


async def to_code(config):
    from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID

    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
