import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID, CONF_ICON
from .. import (
    JngeWindSolarController,
    CONF_JNGE_WIND_SOLAR_CONTROLLER_ID,
    jnge_wind_solar_controller_ns,
)
from ..const import CONF_LOAD, CONF_CHARGING

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

CONF_BUZZER = "buzzer"
CONF_STREET_LIGHT_MODE = "street_light_mode"

ICON_BUZZER = "mdi:volume-high"
ICON_STREET_LIGHT_MODE = "mdi:outdoor-lamp"
ICON_CHARGING = "mdi:battery-charging-50"
ICON_LOAD = "mdi:power-plug"

SWITCHES = {
    CONF_BUZZER: 0x1039,
    CONF_STREET_LIGHT_MODE: 0x1036,
    CONF_CHARGING: 0x1038,
    CONF_LOAD: 0x103C,
}

JngeSwitch = jnge_wind_solar_controller_ns.class_(
    "JngeSwitch", switch.Switch, cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_JNGE_WIND_SOLAR_CONTROLLER_ID): cv.use_id(
            JngeWindSolarController
        ),
        cv.Optional(CONF_BUZZER): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(JngeSwitch),
                cv.Optional(CONF_ICON, default=ICON_BUZZER): switch.icon,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_STREET_LIGHT_MODE): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(JngeSwitch),
                cv.Optional(CONF_ICON, default=ICON_STREET_LIGHT_MODE): switch.icon,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_CHARGING): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(JngeSwitch),
                cv.Optional(CONF_ICON, default=ICON_CHARGING): switch.icon,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_LOAD): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(JngeSwitch),
                cv.Optional(CONF_ICON, default=ICON_LOAD): switch.icon,
            }
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


def to_code(config):
    hub = yield cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key, address in SWITCHES.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            yield cg.register_component(var, conf)
            yield switch.register_switch(var, conf)
            cg.add(getattr(hub, f"set_{key}_switch")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))