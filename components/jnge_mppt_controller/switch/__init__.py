import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import CONF_ID, ENTITY_CATEGORY_CONFIG

from .. import (
    CONF_JNGE_MPPT_CONTROLLER_ID,
    JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA,
    jnge_mppt_controller_ns,
)
from ..const import CONF_CHARGING, CONF_LOAD

DEPENDENCIES = ["jnge_mppt_controller"]

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

JngeSwitch = jnge_mppt_controller_ns.class_("JngeSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_BUZZER): switch.switch_schema(
            JngeSwitch, icon=ICON_BUZZER, entity_category=ENTITY_CATEGORY_CONFIG
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_STREET_LIGHT_MODE): switch.switch_schema(
            JngeSwitch,
            icon=ICON_STREET_LIGHT_MODE,
            entity_category=ENTITY_CATEGORY_CONFIG,
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
    hub = await cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key, address in SWITCHES.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await switch.register_switch(var, conf)
            cg.add(getattr(hub, f"set_{key}_switch")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
