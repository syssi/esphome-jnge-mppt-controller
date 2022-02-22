# esphome-jnge-mppt-controller

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor and control a JN-MPPT or JN-W/S Controller via RS485

![Lovelace entities card](lovelace-entities-card.png "Lovelace entities card")


## Supported devices

* JN-12-W300/S300, JN-12-W500/S500 Wind and Solar Hybrid Controller
* JN-24-W600/S600, JN-24-W800/S800 Wind and Solar Hybrid Controller
* JN-48-W800/S800, JN-48-W1000/S1000 Wind and Solar Hybrid Controller

## Configuration

```yaml
substitutions:
  name: jnge-wind-solar-hybrid
  status: "${name} status"
  config: "${name} config"

esphome:
  name: ${name}
  platform: ESP32
  board: esp-wrover-kit

external_components:
  - source: github://syssi/esphome-jnge-mppt-controller@main
    refresh: 0s

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

ota:
logger:
  level: VERY_VERBOSE
  logs:
    api.service: WARN
    ota: WARN
    wif: WARN
    sensor: DEBUG

mqtt:
  broker: !secret mqtt_host
  username: !secret mqtt_username
  password: !secret mqtt_password
  id: mqtt_client

uart:
  baud_rate: 9600
  tx_pin: GPIO14
  rx_pin: GPIO4
  # debug:
  #   direction: BOTH

jnge_wind_solar_controller:
  update_interval: 2s

binary_sensor:
  - platform: jnge_wind_solar_controller
    load_detected:
      name: "${status} load detected"
    load:
      name: "${status} load"
    charging:
      name: "${status} charging"

sensor:
  - platform: jnge_wind_solar_controller
    # status
    firmware_version:
      name: "${status} firmware version"
    peak_pv_charging_rating:
      name: "${status} peak pv charging rating"
    peak_fan_charging_rating:
      name: "${status} peak fan charging rating"
    pv_voltage:
      name: "${status} pv voltage"
    fan_voltage:
      name: "${status} fan voltage"
    battery_voltage:
      name: "${status} battery voltage"
    pv_charging_current:
      name: "${status} pv charging current"
    fan_charging_current:
      name: "${status} fan charging current"
    pv_charging_power:
      name: "${status} pv charging power"
    fan_charging_power:
      name: "${status} fan charging power"
    pv_total_energy:
      name: "${status} pv total energy"
    fan_total_energy:
      name: "${status} fan total energy"
    operation_mode_id:
      name: "${status} operation mode id"
    battery_strings:
      name: "${status} battery strings"
    battery_voltage_level:
      name: "${status} battery voltage level"
    error_bitmask:
      name: "${status} error bitmask"


switch:
  - platform: jnge_wind_solar_controller
    street_light_mode:
      name: "${config} street light mode"
    charging:
      name: "${config} charging"
    load:
      name: "${config} load"

text_sensor:
  - platform: jnge_wind_solar_controller
    battery_type:
      name: "${status} battery type"
    errors:
      name: "${status} errors"
    operation_mode:
      name: "${status} operation mode"
```

If you use Home Assistant you should replace the `mqtt:` component with the native `api:`.

## Example response all sensors enabled

```
```

## Known issues

* A command queue would be nice

## Missing features

* Schedule configuration retrieval polling interval independent ([#3][i3])
* Register service to change the device configuration ([#4][i4])

[i3]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/3
[i4]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/4
