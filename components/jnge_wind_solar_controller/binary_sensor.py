import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA
from .const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

# CONF_CHARGING = "charging"
# CONF_LOAD = "load"
CONF_LOAD_DETECTED = "load_detected"

# key: binary_sensor_schema kwargs
BINARY_SENSOR_DEFS = {
    CONF_CHARGING: {
        "icon": "mdi:battery-charging-50",
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_LOAD: {
        "icon": "mdi:lightbulb-on",
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_LOAD_DETECTED: {
        "icon": "mdi:lightbulb-on",
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
}

BINARY_SENSORS = list(BINARY_SENSOR_DEFS)

CONFIG_SCHEMA = JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): binary_sensor.binary_sensor_schema(**kwargs)
        for key, kwargs in BINARY_SENSOR_DEFS.items()
    }
)


async def to_code(config):
    from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID

    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = await binary_sensor.new_binary_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
