import esphome.codegen as cg
from esphome.components import jnge_modbus
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

AUTO_LOAD = [
    "jnge_modbus",
    "sensor",
]
MULTI_CONF = True

CONF_JNGE_G_SERIES_ID = "jnge_g_series_id"

UNIT_HOURS = "h"

jnge_g_series_ns = cg.esphome_ns.namespace("jnge_g_series")
JngeGSeries = jnge_g_series_ns.class_(
    "JngeGSeries", cg.PollingComponent, jnge_modbus.JngeModbusDevice
)

JNGE_G_SERIES_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_G_SERIES_ID): cv.use_id(JngeGSeries),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(JngeGSeries),
        }
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(jnge_modbus.jnge_modbus_device_schema(0x06))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await jnge_modbus.register_jnge_modbus_device(var, config)
