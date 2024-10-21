import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID

from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID, JngeWindSolarController
from .const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

# CONF_CHARGING = "charging"
# CONF_LOAD = "load"
CONF_LOAD_DETECTED = "load_detected"

BINARY_SENSORS = [
    CONF_CHARGING,
    CONF_LOAD,
    CONF_LOAD_DETECTED,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_WIND_SOLAR_CONTROLLER_ID): cv.use_id(
            JngeWindSolarController
        ),
        cv.Optional(CONF_CHARGING): binary_sensor.binary_sensor_schema(
            icon="mdi:battery-charging-50"
        ),
        cv.Optional(CONF_LOAD): binary_sensor.binary_sensor_schema(
            icon="mdi:lightbulb-on"
        ),
        cv.Optional(CONF_LOAD_DETECTED): binary_sensor.binary_sensor_schema(
            icon="mdi:lightbulb-on"
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
