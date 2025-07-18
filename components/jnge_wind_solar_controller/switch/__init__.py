import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import CONF_ID

from .. import (
    JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA,
    jnge_wind_solar_controller_ns,
)
from ..const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_wind_solar_controller"]

CODEOWNERS = ["@syssi"]

CONF_BUZZER = "buzzer"
CONF_STREET_LIGHT_MODE = "street_light_mode"

ICON_STREET_LIGHT_MODE = "mdi:outdoor-lamp"
ICON_CHARGING = "mdi:battery-charging-50"
ICON_LOAD = "mdi:power-plug"

SWITCHES = {
    CONF_STREET_LIGHT_MODE: 0x1033,
    CONF_CHARGING: 0x103B,
    CONF_LOAD: 0x103C,
}

JngeSwitch = jnge_wind_solar_controller_ns.class_(
    "JngeSwitch", switch.Switch, cg.Component
)

CONFIG_SCHEMA = JNGE_WIND_SOLAR_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_STREET_LIGHT_MODE): switch.switch_schema(
            JngeSwitch, icon=ICON_STREET_LIGHT_MODE
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_CHARGING): switch.switch_schema(
            JngeSwitch, icon=ICON_CHARGING
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_LOAD): switch.switch_schema(JngeSwitch, icon=ICON_LOAD).extend(
            cv.COMPONENT_SCHEMA
        ),
    }
)


async def to_code(config):
    from .. import CONF_JNGE_WIND_SOLAR_CONTROLLER_ID

    hub = await cg.get_variable(config[CONF_JNGE_WIND_SOLAR_CONTROLLER_ID])
    for key, address in SWITCHES.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await switch.register_switch(var, conf)
            cg.add(getattr(hub, f"set_{key}_switch")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
