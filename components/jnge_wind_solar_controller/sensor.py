import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
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
    UNIT_AMPERE,
    UNIT_EMPTY,
    UNIT_VOLT,
    UNIT_WATT,
)

from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID, JngeWindSolarController

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

SENSORS = [
    CONF_FIRMWARE_VERSION,
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
UNIT_KILO_WATT_HOURS = "kWh"
UNIT_MILLIVOLT = "mV"
UNIT_MILLIVOLT_PER_CELSIUS = "mV/°C"

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_WIND_SOLAR_CONTROLLER_ID): cv.use_id(
            JngeWindSolarController
        ),
        # status
        cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
            UNIT_EMPTY, ICON_EMPTY, 0, DEVICE_CLASS_EMPTY, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_PV_VOLTAGE): sensor.sensor_schema(
            UNIT_VOLT, ICON_EMPTY, 1, DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_FAN_VOLTAGE): sensor.sensor_schema(
            UNIT_VOLT, ICON_EMPTY, 1, DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_BATTERY_VOLTAGE): sensor.sensor_schema(
            UNIT_VOLT, ICON_EMPTY, 1, DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_PV_CHARGING_CURRENT): sensor.sensor_schema(
            UNIT_AMPERE,
            ICON_EMPTY,
            1,
            DEVICE_CLASS_CURRENT,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FAN_CHARGING_CURRENT): sensor.sensor_schema(
            UNIT_AMPERE,
            ICON_EMPTY,
            1,
            DEVICE_CLASS_CURRENT,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PV_CHARGING_POWER): sensor.sensor_schema(
            UNIT_WATT, ICON_EMPTY, 1, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_FAN_CHARGING_POWER): sensor.sensor_schema(
            UNIT_WATT, ICON_EMPTY, 1, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT
        ),
        cv.Optional(CONF_PV_TOTAL_ENERGY): sensor.sensor_schema(
            UNIT_KILO_WATT_HOURS,
            ICON_COUNTER,
            1,
            DEVICE_CLASS_ENERGY,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FAN_TOTAL_ENERGY): sensor.sensor_schema(
            UNIT_KILO_WATT_HOURS,
            ICON_COUNTER,
            1,
            DEVICE_CLASS_ENERGY,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OPERATION_MODE_ID): sensor.sensor_schema(
            UNIT_EMPTY,
            ICON_OPERATION_MODE,
            0,
            DEVICE_CLASS_EMPTY,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_STRINGS): sensor.sensor_schema(
            UNIT_EMPTY,
            ICON_BATTERY_STRINGS,
            0,
            DEVICE_CLASS_EMPTY,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BATTERY_VOLTAGE_LEVEL): sensor.sensor_schema(
            UNIT_VOLT,
            ICON_EMPTY,
            0,
            DEVICE_CLASS_VOLTAGE,
            STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_ERROR_BITMASK): sensor.sensor_schema(
            UNIT_EMPTY,
            ICON_ERROR_BITMASK,
            0,
            DEVICE_CLASS_EMPTY,
            STATE_CLASS_MEASUREMENT,
        ),
    }
)


def to_code(config):
    hub = yield cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = yield sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
