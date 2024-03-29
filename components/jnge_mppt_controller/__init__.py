import esphome.codegen as cg
from esphome.components import jnge_modbus
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

AUTO_LOAD = [
    "jnge_modbus",
    "binary_sensor",
    "number",
    "sensor",
    "select",
    "switch",
    "text_sensor",
]
MULTI_CONF = True

CONF_JNGE_MPPT_CONTROLLER_ID = "jnge_mppt_controller_id"
CONF_ENABLE_FAKE_TRAFFIC = "enable_fake_traffic"
CONF_SUPPRESS_BATTERY_TEMPERATURE_ERRORS = "suppress_battery_temperature_errors"

UNIT_HOURS = "h"

jnge_mppt_controller_ns = cg.esphome_ns.namespace("jnge_mppt_controller")
JngeMpptController = jnge_mppt_controller_ns.class_(
    "JngeMpptController", cg.PollingComponent, jnge_modbus.JngeModbusDevice
)

JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_MPPT_CONTROLLER_ID): cv.use_id(JngeMpptController),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(JngeMpptController),
            cv.Optional(CONF_ENABLE_FAKE_TRAFFIC, default=False): cv.boolean,
            cv.Optional(
                CONF_SUPPRESS_BATTERY_TEMPERATURE_ERRORS, default=False
            ): cv.boolean,
        }
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(jnge_modbus.jnge_modbus_device_schema(0x06))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await jnge_modbus.register_jnge_modbus_device(var, config)

    cg.add(var.set_enable_fake_traffic(config[CONF_ENABLE_FAKE_TRAFFIC]))
    cg.add(
        var.set_suppress_battery_temperature_errors(
            config[CONF_SUPPRESS_BATTERY_TEMPERATURE_ERRORS]
        )
    )
