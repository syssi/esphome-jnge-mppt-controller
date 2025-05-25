import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID

from . import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID, JngeWindSolarController

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

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_WIND_SOLAR_CONTROLLER_ID): cv.use_id(
            JngeWindSolarController
        ),
        cv.Optional(CONF_OPERATION_MODE): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon=ICON_OPERATION_MODE
        ),
        cv.Optional(CONF_ERRORS): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon=ICON_ERRORS
        ),
        cv.Optional(CONF_BATTERY_TYPE): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon=ICON_BATTERY_TYPE
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key in TEXT_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await text_sensor.register_text_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))
