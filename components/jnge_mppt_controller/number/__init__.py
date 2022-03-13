import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
    CONF_ID,
    CONF_MODE,
    CONF_MAX_VALUE,
    CONF_MIN_VALUE,
    CONF_STEP,
    CONF_UNIT_OF_MEASUREMENT,
    ICON_EMPTY,
    UNIT_VOLT,
    UNIT_EMPTY,
    ENTITY_CATEGORY_CONFIG,
)

from .. import (
    CONF_JNGE_MPPT_CONTROLLER_ID,
    JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA,
    UNIT_HOURS,
    jnge_mppt_controller_ns,
)

DEPENDENCIES = ["jnge_mppt_controller"]

CODEOWNERS = ["@syssi"]

DEFAULT_STEP = 1

CONF_BATTERY_OVERVOLTAGE = "battery_overvoltage"
CONF_CHARGING_LIMIT_VOLTAGE = "charging_limit_voltage"
CONF_BATTERY_OVERVOLTAGE_RECOVERY = "battery_overvoltage_recovery"
CONF_EQUALIZING_CHARGING_VOLTAGE = "equalizing_charging_voltage"
CONF_BOOST_CHARGING_VOLTAGE = "boost_charging_voltage"
CONF_BOOST_CHARGING_RETURN_VOLTAGE = "boost_charging_return_voltage"
CONF_FLOATING_CHARGE_VOLTAGE = "floating_charge_voltage"
CONF_OVER_DISCHARGE_VOLTAGE = "over_discharge_voltage"
CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE = "over_discharge_recovery_voltage"
CONF_BATTERY_UNDERVOLTAGE = "battery_undervoltage"
CONF_EQUALIZATION_CHARGING_TIME = "equalization_charging_time"
CONF_IMPROVE_CHARGING_TIME = "improve_charging_time"
CONF_LIGHT_CONTROL_ON_VOLTAGE = "light_control_on_voltage"
CONF_LIGHT_CONTROL_OFF_VOLTAGE = "light_control_off_voltage"
CONF_LIGHT_CONTROL_ON_PERIOD_1 = "light_control_on_period_1"
CONF_LIGHT_CONTROL_ON_PERIOD_2 = "light_control_on_period_2"
CONF_LOAD_TURN_OFF_TIME = "load_turn_off_time"
CONF_BATTERY_STRINGS = "battery_strings"

NUMBERS = {
    CONF_BATTERY_OVERVOLTAGE: 0x1024,  # 12-18V, 28-36V, 56-62V, 112-144V
    CONF_CHARGING_LIMIT_VOLTAGE: 0x1025,  # 12.9-16.9V, 25.7-33.7V, 51.6-62V, 103-105V
    CONF_BATTERY_OVERVOLTAGE_RECOVERY: 0x1026,  # 13-17V, 26-34V, 52-62V, 104-136V
    CONF_EQUALIZING_CHARGING_VOLTAGE: 0x1027,  # 12.7-16.7V, 25.4-33.4V, 50.8-62V, 102-134V
    CONF_BOOST_CHARGING_VOLTAGE: 0x1028,  # 12.4-16.4V, 24.8-32.8V, 49.6-62V, 99-131V
    CONF_BOOST_CHARGING_RETURN_VOLTAGE: 0x1029,  # 11.2-15.2V, 22.4-30.4V, 44.8-62V, 90-122V
    CONF_FLOATING_CHARGE_VOLTAGE: 0x102A,  # 11.8-15.8V, 23.6-31.6V, 47.2-62V, 94-126V
    CONF_OVER_DISCHARGE_VOLTAGE: 0x102B,  # 8.8-12.8V, 17.6-25.6V, 35.2-51.2V, 70-102V
    CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE: 0x102C,  # 11.1-15.1V, 22.2-30.2V, 44.4-60.4V, 89-121V
    CONF_BATTERY_UNDERVOLTAGE: 0x102D,
    CONF_EQUALIZATION_CHARGING_TIME: 0x102E,  # 1/2/3H
    CONF_IMPROVE_CHARGING_TIME: 0x102F,  # 1/2/3H
    CONF_LIGHT_CONTROL_ON_VOLTAGE: 0x1032,  # 5-11V
    CONF_LIGHT_CONTROL_OFF_VOLTAGE: 0x1033,  # 5-11V
    CONF_LIGHT_CONTROL_ON_PERIOD_1: 0x1034,  # H
    CONF_LIGHT_CONTROL_ON_PERIOD_2: 0x1035,  # H
    CONF_LOAD_TURN_OFF_TIME: 0x1037,  # H
    CONF_BATTERY_STRINGS: 0x103A,  # n
}

JngeNumber = jnge_mppt_controller_ns.class_("JngeNumber", number.Number, cg.Component)

JNGENUMBER_SCHEMA = number.NUMBER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(JngeNumber),
        cv.Optional(CONF_ICON, default=ICON_EMPTY): number.icon,
        cv.Optional(CONF_STEP, default=0.1): cv.float_,
        cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_VOLT): cv.string_strict,
        cv.Optional(CONF_MODE, default="BOX"): cv.enum(number.NUMBER_MODES, upper=True),
        cv.Optional(
            CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
        ): cv.entity_category,
    }
).extend(cv.COMPONENT_SCHEMA)

CONFIG_SCHEMA = JNGE_MPPT_CONTROLLER_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_BATTERY_OVERVOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=56.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_CHARGING_LIMIT_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=51.6): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_BATTERY_OVERVOLTAGE_RECOVERY): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=52.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_EQUALIZING_CHARGING_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=50.8): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_BOOST_CHARGING_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=49.6): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_BOOST_CHARGING_RETURN_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=44.8): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_FLOATING_CHARGE_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=47.2): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=62.0): cv.float_,
            }
        ),
        cv.Optional(CONF_OVER_DISCHARGE_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=35.2): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=51.2): cv.float_,
            }
        ),
        cv.Optional(CONF_OVER_DISCHARGE_RECOVERY_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=44.4): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=60.4): cv.float_,
            }
        ),
        cv.Optional(CONF_BATTERY_UNDERVOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=32): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=51.2): cv.float_,
            }
        ),
        cv.Optional(CONF_EQUALIZATION_CHARGING_TIME): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=3): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_HOURS
                ): cv.string_strict,
            }
        ),
        cv.Optional(CONF_IMPROVE_CHARGING_TIME): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=3): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_HOURS
                ): cv.string_strict,
            }
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=5.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=11.0): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
            }
        ),
        cv.Optional(CONF_LIGHT_CONTROL_OFF_VOLTAGE): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=5.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=11.0): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
            }
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_PERIOD_1): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=24): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_HOURS
                ): cv.string_strict,
            }
        ),
        cv.Optional(CONF_LIGHT_CONTROL_ON_PERIOD_2): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=24): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_HOURS
                ): cv.string_strict,
            }
        ),
        cv.Optional(CONF_LOAD_TURN_OFF_TIME): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=24): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_HOURS
                ): cv.string_strict,
            }
        ),
        cv.Optional(CONF_BATTERY_STRINGS): JNGENUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=1): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=32): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(
                    CONF_UNIT_OF_MEASUREMENT, default=UNIT_EMPTY
                ): cv.string_strict,
            }
        ),
    }
)


def to_code(config):
    hub = yield cg.get_variable(config[CONF_JNGE_MPPT_CONTROLLER_ID])
    for key, address in NUMBERS.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            yield cg.register_component(var, conf)
            yield number.register_number(
                var,
                conf,
                min_value=conf[CONF_MIN_VALUE],
                max_value=conf[CONF_MAX_VALUE],
                step=conf[CONF_STEP],
            )
            cg.add(getattr(hub, f"set_{key}_number")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
