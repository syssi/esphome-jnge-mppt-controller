import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import output
from esphome.const import CONF_ID, CONF_VALUE

from .. import (
    CONF_JNGE_MPPT_CONTROLLER_ID,
    JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA,
    jnge_mppt_controller_ns,
)

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

JngeOutput = jnge_mppt_controller_ns.class_(
    "JngeOutput", output.FloatOutput, cg.Component
)
SetOutputAction = jnge_mppt_controller_ns.class_("SetOutputAction", automation.Action)

CONF_POSSIBLE_VALUES = "possible_values"

CONF_BATTERY_RECHARGE_VOLTAGE = "battery_recharge_voltage"


TYPES = {
    CONF_BATTERY_RECHARGE_VOLTAGE: (
        [44.0, 45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0],
        "PBCV%02.1f",
    ),
}

CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(type): output.FLOAT_OUTPUT_SCHEMA.extend(
            {
                cv.Required(CONF_ID): cv.declare_id(JngeOutput),
                cv.Optional(CONF_POSSIBLE_VALUES, default=values): cv.All(
                    cv.ensure_list(cv.positive_float), cv.Length(min=1)
                ),
            }
        )
        for type, (values, _) in TYPES.items()
    }
)


async def to_code(config):
    paren = await cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])

    for type, (_, command) in TYPES.items():
        if type in config:
            conf = config[type]
            var = cg.new_Pvariable(conf[CONF_ID])
            await output.register_output(var, conf)
            cg.add(var.set_parent(paren))
            cg.add(var.set_set_command(command))
            if (CONF_POSSIBLE_VALUES) in conf:
                cg.add(var.set_possible_values(conf[CONF_POSSIBLE_VALUES]))


@automation.register_action(
    "output.jnge_mppt_controller.set_level",
    SetOutputAction,
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.use_id(CONF_ID),
            cv.Required(CONF_VALUE): cv.templatable(cv.positive_float),
        }
    ),
)
def output_jnge_mppt_controller_set_level_to_code(
    config, action_id, template_arg, args
):
    paren = yield cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    template_ = yield cg.templatable(config[CONF_VALUE], args, float)
    cg.add(var.set_level(template_))
    yield var
