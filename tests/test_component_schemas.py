"""Schema structure tests for jnge ESPHome component modules."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import components.jnge_g_series as hub_g  # noqa: E402
from components.jnge_g_series import sensor as g_sensor  # noqa: E402
import components.jnge_mppt_controller as hub  # noqa: E402
from components.jnge_mppt_controller import (  # noqa: E402
    binary_sensor,
    sensor,
    switch,  # noqa: E402
    text_sensor,
)
import components.jnge_wind_solar_controller as hub_wsc  # noqa: E402
from components.jnge_wind_solar_controller import (  # noqa: E402
    binary_sensor as wsc_binary_sensor,
    sensor as wsc_sensor,
    switch as wsc_switch,  # noqa: E402
    text_sensor as wsc_text_sensor,
)


class TestHubConstants:
    def test_conf_ids_defined(self):
        assert hub.CONF_JNGE_MPPT_CONTROLLER_ID == "jnge_mppt_controller_id"
        assert (
            hub_wsc.CONF_JNGE_WIND_SOLAR_CONTROLLER_ID
            == "jnge_wind_solar_controller_id"
        )
        assert hub_g.CONF_JNGE_G_SERIES_ID == "jnge_g_series_id"


class TestJngeMpptSensorLists:
    def test_sensor_defs_completeness(self):
        assert "battery_voltage" in sensor.SENSOR_DEFS
        assert sensor.CONF_PV_VOLTAGE in sensor.SENSOR_DEFS
        assert sensor.CONF_CHARGING_CURRENT in sensor.SENSOR_DEFS
        assert len(sensor.SENSOR_DEFS) == 41

    def test_no_cell_keys(self):
        for key in sensor.SENSOR_DEFS:
            assert isinstance(key, str)


class TestJngeMpptBinarySensorConstants:
    def test_binary_sensor_defs_dict(self):
        from components.jnge_mppt_controller.const import CONF_CHARGING, CONF_LOAD

        assert CONF_CHARGING in binary_sensor.BINARY_SENSOR_DEFS
        assert CONF_LOAD in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_FAN_RUNNING in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_LOAD_DETECTED in binary_sensor.BINARY_SENSOR_DEFS
        assert len(binary_sensor.BINARY_SENSOR_DEFS) == 4


class TestJngeMpptTextSensorConstants:
    def test_text_sensors_list(self):
        assert text_sensor.CONF_ERRORS in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_OPERATION_MODE in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_BATTERY_TYPE in text_sensor.TEXT_SENSORS
        assert len(text_sensor.TEXT_SENSORS) == 3


class TestJngeMpptSwitchConstants:
    def test_switches_dict(self):
        assert switch.CONF_BUZZER in switch.SWITCHES
        assert switch.CONF_CHARGING in switch.SWITCHES
        assert switch.CONF_LOAD in switch.SWITCHES
        assert len(switch.SWITCHES) == 4

    def test_switch_addresses_are_unique(self):
        addresses = list(switch.SWITCHES.values())
        assert len(addresses) == len(set(addresses))


class TestJngeWindSolarSensorLists:
    def test_sensor_defs_completeness(self):
        assert "battery_voltage" in wsc_sensor.SENSOR_DEFS
        assert wsc_sensor.CONF_PV_VOLTAGE in wsc_sensor.SENSOR_DEFS
        assert len(wsc_sensor.SENSOR_DEFS) == 16


class TestJngeWindSolarBinarySensorConstants:
    def test_binary_sensor_defs_dict(self):
        from components.jnge_wind_solar_controller.const import CONF_CHARGING, CONF_LOAD

        assert CONF_CHARGING in wsc_binary_sensor.BINARY_SENSOR_DEFS
        assert CONF_LOAD in wsc_binary_sensor.BINARY_SENSOR_DEFS
        assert (
            wsc_binary_sensor.CONF_LOAD_DETECTED in wsc_binary_sensor.BINARY_SENSOR_DEFS
        )
        assert len(wsc_binary_sensor.BINARY_SENSOR_DEFS) == 3


class TestJngeWindSolarTextSensorConstants:
    def test_text_sensors_list(self):
        assert wsc_text_sensor.CONF_ERRORS in wsc_text_sensor.TEXT_SENSORS
        assert wsc_text_sensor.CONF_OPERATION_MODE in wsc_text_sensor.TEXT_SENSORS
        assert len(wsc_text_sensor.TEXT_SENSORS) == 3


class TestJngeWindSolarSwitchConstants:
    def test_switches_dict(self):
        assert wsc_switch.CONF_CHARGING in wsc_switch.SWITCHES
        assert wsc_switch.CONF_LOAD in wsc_switch.SWITCHES
        assert len(wsc_switch.SWITCHES) == 3

    def test_switch_addresses_are_unique(self):
        addresses = list(wsc_switch.SWITCHES.values())
        assert len(addresses) == len(set(addresses))


class TestJngeGSeriesSensorLists:
    def test_sensor_defs_completeness(self):
        assert len(g_sensor.SENSOR_DEFS) == 9
