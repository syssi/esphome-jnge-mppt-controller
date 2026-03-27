import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

CONF_BATTERY_TYPE = "battery_type"
CONF_ERRORS = "errors"
CONF_OPERATION_MODE = "operation_mode"

ICON_BATTERY_TYPE = "mdi:car-battery"
ICON_ERRORS = "mdi:alert-circle-outline"
ICON_OPERATION_MODE = "mdi:heart-pulse"

TEXT_SENSORS = [
    CONF_OPERATION_MODE,
    CONF_ERRORS,
    CONF_BATTERY_TYPE,
]

CONFIG_SCHEMA = JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_OPERATION_MODE): text_sensor.text_sensor_schema(
            icon=ICON_OPERATION_MODE
        ),
        cv.Optional(CONF_ERRORS): text_sensor.text_sensor_schema(
            icon=ICON_ERRORS,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_BATTERY_TYPE): text_sensor.text_sensor_schema(
            icon=ICON_BATTERY_TYPE
        ),
    }
)


async def to_code(config):
    from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID

    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in TEXT_SENSORS:
        if key in config:
            conf = config[key]
            sens = await text_sensor.new_text_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))
