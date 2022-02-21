import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import jnge_modbus
from esphome.const import CONF_ID

AUTO_LOAD = ["jnge_modbus", "binary_sensor", "sensor", "switch", "text_sensor"]
CODEOWNERS = ["@syssi"]
MULTI_CONF = True

CONF_JNGE_WIND_SOLAR_CONTROLLER_ID = "jnge_wind_solar_controller_id"

jnge_wind_solar_controller_ns = cg.esphome_ns.namespace("jnge_wind_solar_controller")
JngeWindSolarController = jnge_wind_solar_controller_ns.class_(
    "JngeWindSolarController", cg.PollingComponent, jnge_modbus.JngeModbusDevice
)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(JngeWindSolarController)})
    .extend(cv.polling_component_schema("5s"))
    .extend(jnge_modbus.jnge_modbus_device_schema(0x06))
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield jnge_modbus.register_jnge_modbus_device(var, config)
