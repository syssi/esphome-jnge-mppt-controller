import esphome.codegen as cg
from esphome.components import select
import esphome.config_validation as cv

from .. import (
    CONF_JNGE_MPPT_CONTROLLER_ID,
    JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA,
    jnge_mppt_controller_ns,
)

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

CONF_BATTERY_TYPE = "battery_type"
CONF_OPTIONSMAP = "optionsmap"

JngeSelect = jnge_mppt_controller_ns.class_("JngeSelect", select.Select, cg.Component)


def ensure_option_map(value):
    cv.check_not_templatable(value)
    option = cv.All(cv.int_range(0, 2**8 - 1))
    mapping = cv.All(cv.string_strict)
    options_map_schema = cv.Schema({option: mapping})
    value = options_map_schema(value)

    all_values = list(value.keys())
    unique_values = set(value.keys())
    if len(all_values) != len(unique_values):
        raise cv.Invalid("Mapping values must be unique.")

    return value


SELECTS = {
    CONF_BATTERY_TYPE: 0x103B,
}

JNGESELECT_SCHEMA = select.SELECT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(JngeSelect),
        cv.Optional(CONF_OPTIONSMAP): ensure_option_map,
    }
).extend(cv.COMPONENT_SCHEMA)


CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {cv.Optional(type): JNGESELECT_SCHEMA for type in SELECTS}
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])

    for key, address in SELECTS.items():
        if key in config:
            conf = config[key]
            options_map = conf[CONF_OPTIONSMAP]
            var = await select.new_select(config, options=list(options_map.values()))
            await cg.register_component(var, config)
            cg.add(var.set_select_mappings(list(options_map.keys())))

            cg.add(getattr(hub, f"set_{key}_select")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
