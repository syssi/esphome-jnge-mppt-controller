import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, CONF_ICON
from . import JngeMpptController, CONF_JNGE_MPPT_CONTROLLER_ID

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

# readonly
CONF_LOAD_DETECTED = "load_detected"
CONF_FAN_RUNNING = "fan_running"
CONF_LOAD = "load"
CONF_CHARGING = "charging"

ICON_CHARGING = "mdi:battery-charging-50"
ICON_FAN_RUNNING = "mdi:fan"
ICON_LOAD = "mdi:lightbulb-on"
ICON_LOAD_DETECTED = "mdi:lightbulb-on"

BINARY_SENSORS = [
    CONF_LOAD_DETECTED,
    CONF_FAN_RUNNING,
    CONF_LOAD,
    CONF_CHARGING,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_MPPT_CONTROLLER_ID): cv.use_id(JngeMpptController),
        cv.Optional(CONF_LOAD_DETECTED): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_LOAD_DETECTED): cv.icon,
            }
        ),
        cv.Optional(CONF_FAN_RUNNING): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_FAN_RUNNING): cv.icon,
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
    hub = yield cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            yield binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
