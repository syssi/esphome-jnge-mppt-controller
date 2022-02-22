import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ICON, CONF_ID

from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID, JngeWindSolarController
from .const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

# readonly
CONF_LOAD_DETECTED = "load_detected"

ICON_CHARGING = "mdi:battery-charging-50"
ICON_LOAD = "mdi:lightbulb-on"
ICON_LOAD_DETECTED = "mdi:lightbulb-on"

BINARY_SENSORS = [
    CONF_LOAD_DETECTED,
    CONF_LOAD,
    CONF_CHARGING,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_WIND_SOLAR_CONTROLLER_ID): cv.use_id(
            JngeWindSolarController
        ),
        cv.Optional(CONF_LOAD_DETECTED): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_LOAD_DETECTED): cv.icon,
            }
        ),
        cv.Optional(CONF_LOAD): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_LOAD): cv.icon,
            }
        ),
        cv.Optional(CONF_CHARGING): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_CHARGING): cv.icon,
            }
        ),
    }
)


def to_code(config):
    hub = yield cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            yield binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
