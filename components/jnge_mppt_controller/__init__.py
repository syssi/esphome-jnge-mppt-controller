import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import jnge_modbus
from esphome.const import CONF_ID

AUTO_LOAD = ["jnge_modbus", "binary_sensor", "sensor", "switch", "text_sensor"]
CODEOWNERS = ["@syssi"]
MULTI_CONF = True

CONF_JNGE_MPPT_CONTROLLER_ID = "jnge_mppt_controller_id"
CONF_ENABLE_FAKE_TRAFFIC = "enable_fake_traffic"
CONF_SUPPRESS_BATTERY_TEMPERATURE_ERRORS = "suppress_battery_temperature_errors"

jnge_mppt_controller_ns = cg.esphome_ns.namespace("jnge_mppt_controller")
JngeMpptController = jnge_mppt_controller_ns.class_(
    "JngeMpptController", cg.PollingComponent, jnge_modbus.JngeModbusDevice
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


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield jnge_modbus.register_jnge_modbus_device(var, config)

    cg.add(var.set_enable_fake_traffic(config[CONF_ENABLE_FAKE_TRAFFIC]))
    cg.add(
        var.set_suppress_battery_temperature_errors(
            config[CONF_SUPPRESS_BATTERY_TEMPERATURE_ERRORS]
        )
    )
