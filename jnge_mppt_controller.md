# esphome-jnge-mppt-controller

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor and control a JN-MPPT or JN-W/S Controller via RS485

![Lovelace entities card](lovelace-entities-card.png "Lovelace entities card")


## Supported devices

* JN-MPPT-MINI Buck Solar Charge Controller `<2021/01` (12V / 24V / 48V)
* JN-MPPT-MINI Buck Solar Charge Controller `2021` (12V / 24V)
* JN-MPPT-AL Buck Solar Charge Controller (12V / 24V / 48V)
* JN-MPPT-BL Buck Solar Charge Controller (12V / 24V / 48V)
* JN-MPPT-CL Buck Solar Charge Controller (12V / 24V / 48V)

|                                       | JN-MPPT-MINI 2021      | JN-MPPT-MINI <2021/01 | JN-MPPT-AL           | JN-MPPT-BL                       | JN-MPPT-CL                          |
| ------------------------------------- | ---------------------- | --------------------- | -------------------- | -------------------------------- | ----------------------------------- |
| **Battery system voltage**            | 12V / 24V              | 12V / 24V / 48V       | 12V / 24V / 48V      | 12V / 24V / 48V                  | 12V / 24V / 48V / 96                |
| **PV max. input current**             | 10A<br>20A<br>30A      | 10A<br>20A<br>30A     | 30A<br>40A<br>50A    | 30A<br>40A<br>50A<br>60A<br>70A  | 50A<br>60A<br>80A<br>100A<br>120A   |
| **Maximum charging current**          | 10A<br>20A<br>30A      | 10A<br>20A<br>30A     | 30A<br>40A<br>50A    | 30A<br>40A<br>50A<br>60A<br>70A  | 50A<br>60A<br>80A<br>100A<br>120A   |
| **Output max. current**               |  7A<br>14A<br>21A      | 10A<br>15A<br>15A     | 21A<br>28A<br>35A    | 21A<br>28A<br>35A<br>42A<br>49A  | --                                  |
| **PV voltage range (VOC), 12V mode**  | 20-100V                | 20-100V               | 20-100V              | 20-100V                          | 20-100V                             |
| **PV voltage range (VOC), 24V mode**  | 40-100V                | 40-145V (150V peak)   | 40-145V (150V peak)  | 40-145V (150V peak)              | 40-145V                             |
| **PV voltage range (VOC), 48V mode**  | --                     | 80-145V (150V peak)   | 80-145V (150V peak)  | 80-145V (150V peak)              | 160-240V                            |
| **PV voltage range (VOC), 96V mode**  | --                     | --                    | --                   | --                               | 160-240V                            |

The manufacturer dropped the 48V support of the JN-MPPT-MINI in 2021. The new and downgraded model can be identified by a white sticker:

```
JN-MPPT_MINI
V:21/24V
C:30A
P:360/720W
2021/04/29
```

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://syssi/esphome-jnge-mppt-controller@main
```

or just use the `esp32-example-jnge-mppt-controller.yaml` / `esp8266-example-jnge-mppt-controller.yaml` as proof of concept:

```bash
# Install esphome
pip3 install esphome

# Clone this external component
git clone https://github.com/syssi/esphome-jnge-mppt-controller.git
cd esphome-jnge-mppt-controller

# Create a secrets.yaml containing some setup specific secrets
cat > secrets.yaml <<EOF
wifi_ssid: MY_WIFI_SSID
wifi_password: MY_WIFI_PASSWORD

mqtt_host: MY_MQTT_HOST
mqtt_username: MY_MQTT_USERNAME
mqtt_password: MY_MQTT_PASSWORD
EOF

# Validate the configuration, create a binary, upload it, and start logs
# If you use a esp8266 run the esp8266-example-jnge-mppt-controller.yaml
esphome run esp32-example-jnge-mppt-controller.yaml
```

## Configuration

```yaml
substitutions:
  name: jn-mppt
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

mqtt:
  broker: !secret mqtt_host
  username: !secret mqtt_username
  password: !secret mqtt_password
  id: mqtt_client

uart:
  baud_rate: 9600
  tx_pin: GPIO14
  rx_pin: GPIO4

jnge_mppt_controller:
  update_interval: 2s

binary_sensor:
  - platform: jnge_mppt_controller
    fan_running:
      name: "${status} fan running"
    load_detected:
      name: "${status} load detected"
    load:
      name: "${status} load"
    charging:
      name: "${status} charging"

sensor:
  - platform: jnge_mppt_controller
    # status
    firmware_version:
      name: "${status} firmware version"
    pv_voltage:
      name: "${status} pv voltage"
    battery_voltage:
      name: "${status} battery voltage"
    channel_a_current:
      name: "${status} channel a current"
    channel_b_current:
      name: "${status} channel b current"
    charging_current:
      name: "${status} charging current"
    charger_temperature:
      name: "${status} charger temperature"
    charging_power:
      name: "${status} charging power"
    discharge_power:
      name: "${status} discharge power"
    battery_capacity:
      name: "${status} battery capacity"
    operation_mode_id:
      name: "${status} operation mode id"
    discharge_current:
      name: "${status} discharge current"
    discharge_times:
      name: "${status} discharge times"
    total_charging_energy:
      name: "${status} total charging energy"
    total_discharge_energy:
      name: "${status} total discharge energy"
    battery_temperature:
      name: "${status} battery temperature"
    error_bitmask:
      name: "${status} error bitmask"
    controller_voltage_level:
      name: "${status} controller voltage level"
    pv_standby_voltage:
      name: "${status} pv standby voltage"
    controller_current_level:
      name: "${status} controller current level"
    battery_strings:
      name: "${status} battery strings"
    battery_temperature_compensation_voltage_point:
      name: "${status} battery temperature compensation voltage point"

    # config
    overvoltage:
      name: "${config} overvoltage"
    charging_limit_voltage:
      name: "${config} charging limit voltage"
    overvoltage_recovery:
      name: "${config} overvoltage recovery"
    equalizing_charging_voltage:
      name: "${config} equalizing charging voltage"
    boost_charging_voltage:
      name: "${config} boost charging voltage"
    boost_charging_return_voltage:
      name: "${config} boost charging return voltage"
    floating_charge_voltage:
      name: "${config} floating charge voltage"
    over_discharge_voltage:
      name: "${config} over discharge voltage"
    over_discharge_recovery_voltage:
      name: "${config} over discharge recovery voltage"
    battery_undervoltage:
      name: "${config} battery undervoltage"
    equalization_charging_time:
      name: "${config} equalization charging time"
    improve_charging_time:
      name: "${config} improve charging time"
    temperature_compensation_coefficient:
      name: "${config} temperature compensation coefficient"
    device_address:
      name: "${config} device address"
    light_control_on_voltage:
      name: "${config} light control on voltage"
    light_control_off_voltage:
      name: "${config} light control off voltage"
    light_control_on_period_1:
      name: "${config} light control on period 1"
    light_control_on_period_2:
      name: "${config} light control on period 2"
    load_turn_off_time:
      name: "${config} load turn off time"

switch:
  - platform: jnge_mppt_controller
    buzzer:
      name: "${config} buzzer"
    street_light_mode:
      name: "${config} street light mode"
    charging:
      name: "${config} charging"
    load:
      name: "${config} load"

text_sensor:
  - platform: jnge_mppt_controller
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
[sensor:127]: 'jn_mppt_mini status firmware version': Sending state 4.00000  with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status pv voltage': Sending state 0.00000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status battery voltage': Sending state 12.10000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status channel a current': Sending state 0.00000 A with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status channel b current': Sending state 0.00000 A with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status charging current': Sending state 0.00000 A with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status charger temperature': Sending state 26.00000 °C with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status charging power': Sending state 0.00000 W with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status discharge power': Sending state 0.00000 W with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status battery capacity': Sending state 40.00000 % with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status operation mode id': Sending state 0.00000  with 0 decimals of accuracy
[text_sensor:015]: 'jn_mppt_mini status operation mode': Sending state 'Not charging'
[binary_sensor:036]: 'jn_mppt_mini status load detected': Sending state OFF
[sensor:127]: 'jn_mppt_mini status discharge current': Sending state 0.00000 A with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status discharge times': Sending state 0.00000  with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status total charging energy': Sending state 0.40000 kWh with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status total discharge energy': Sending state 0.00000 kWh with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status battery temperature': Sending state 0.00000 °C with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status error bitmask': Sending state 24576.00000  with 0 decimals of accuracy
[text_sensor:015]: 'jn_mppt_mini status errors': Sending state 'Battery temperature sensor failure;PV array undervoltage'
[sensor:127]: 'jn_mppt_mini status controller voltage level': Sending state 12.00000 V with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status pv standby voltage': Sending state 11.10000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status controller current level': Sending state 30.00000 A with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini status battery strings': Sending state 1.00000  with 0 decimals of accuracy
[text_sensor:015]: 'jn_mppt_mini status battery type': Sending state 'Lead-Acid'
[binary_sensor:036]: 'jn_mppt_mini status charging': Sending state ON
[binary_sensor:036]: 'jn_mppt_mini status fan running': Sending state OFF
[sensor:127]: 'jn_mppt_mini status battery temperature compensation voltage point': Sending state 0.00000 mV with 0 decimals of accuracy
[binary_sensor:036]: 'jn_mppt_mini status load': Sending state OFF
[sensor:127]: 'jn_mppt_mini config overvoltage': Sending state 15.50000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config charging limit voltage': Sending state 14.90000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config overvoltage recovery': Sending state 15.00000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config equalizing charging voltage': Sending state 14.40000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config boost charging voltage': Sending state 14.40000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config boost charging return voltage': Sending state 13.20000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config floating charge voltage': Sending state 13.80000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config over discharge voltage': Sending state 10.80000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config over discharge recovery voltage': Sending state 13.10000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config battery undervoltage': Sending state 10.80000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config equalization charging time': Sending state 2.00000 h with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config improve charging time': Sending state 1.00000 h with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config temperature compensation coefficient': Sending state 3.00000 mV/°C with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config device address': Sending state 6.00000  with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config light control on voltage': Sending state 5.00000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config light control off voltage': Sending state 6.00000 V with 1 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config light control on period 1': Sending state 24.00000 h with 0 decimals of accuracy
[sensor:127]: 'jn_mppt_mini config light control on period 2': Sending state 0.00000 h with 0 decimals of accuracy
[switch:045]: 'jn_mppt_mini config street light mode': Sending state ON
[sensor:127]: 'jn_mppt_mini config load turn off time': Sending state 0.00000 h with 0 decimals of accuracy
[switch:045]: 'jn_mppt_mini config charging': Sending state ON
[switch:045]: 'jn_mppt_mini config buzzer': Sending state ON
[switch:045]: 'jn_mppt_mini config load': Sending state OFF
```

## Known issues

* A command queue would be nice

## Missing features

* Schedule configuration retrieval polling interval independent ([#3][i3])
* Register service to change the device configuration ([#4][i4])

[i3]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/3
[i4]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/4
