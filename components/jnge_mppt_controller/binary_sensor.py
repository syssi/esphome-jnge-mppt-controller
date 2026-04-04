import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import CONF_JNGE_MPPT_CONTROLLER_ID, JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA
from .const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

# CONF_CHARGING = "charging"
CONF_FAN_RUNNING = "fan_running"
# CONF_LOAD = "load"
CONF_LOAD_DETECTED = "load_detected"

BINARY_SENSOR_DEFS = {
    CONF_CHARGING: {
        "icon": "mdi:battery-charging-50",
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_FAN_RUNNING: {
        "icon": "mdi:fan",
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

CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): binary_sensor.binary_sensor_schema(**kwargs)
        for key, kwargs in BINARY_SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key in BINARY_SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await binary_sensor.new_binary_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
