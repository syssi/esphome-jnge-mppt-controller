# JN-W/S Wind and Solar Hybrid Controller

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

## Supported devices

* JN-12-W300/S300, JN-12-W500/S500 Wind and Solar Hybrid Controller
* JN-24-W600/S600, JN-24-W800/S800 Wind and Solar Hybrid Controller
* JN-48-W800/S800, JN-48-W1000/S1000 Wind and Solar Hybrid Controller

## Schematics

```
                  RS485                      UART
┌────────────┐              ┌──────────┐                ┌─────────┐
│            │              │          │<----- RX ----->│         │
│    JNGE    │<-----B- ---->│  RS485   │<----- TX ----->│ ESP32/  │
│ Controller │<---- A+ ---->│  to TTL  │<----- GND ---->│ ESP8266 │
│            │<--- GND ---->│  module  │<----- 3.3V --->│         │<-- VCC
│            │              │          │                │         │<-- GND
└────────────┘              └──────────┘                └─────────┘
```

Please make sure to power the RS485 module with 3.3V because it affects the TTL (transistor-transistor logic) voltage between RS485 module and ESP.

### RJ45 jack

| Pin     | Purpose      | RS485-to-TTL pin  | Color T-568B |
| :-----: | :----------- | :---------------- | ------------ |
|    1    |              |                   |              |
|    2    |              |                   |              |
|    3    |              |                   |              |
|    4    |              |                   |              |
|  **5**  | **A+**       | **A+**            | Blue-White   |
|  **6**  | **B-**       | **B-**            | Green        |
|  **7**  | **VCC**      |                   | Brown-White  |
|  **8**  | **GND**      | **GND**           | Brown        |

Please be aware of the different RJ45 pinout colors ([T-568A vs. T-568B](images/rj45-colors-t568a-vs-t568.png)).

If the device supports some load (untested!) at pin 7/8 it could be used to power the ESP. A buck converter from 12V to 5V is required in this case.

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://syssi/esphome-jnge-mppt-controller@main
```

or just use the `esp32-example-jnge-wind-solar-controller.yaml` / `esp8266-example-jnge-wind-solar-controller.yaml` as proof of concept:

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
# If you use a esp8266 run the esp8266-example-jnge-wind-solar-controller.yaml
esphome run esp32-example-jnge-wind-solar-controller.yaml
```

If you use Home Assistant please uncomment the native `api` component and remove the `mqtt` section!

## Example response all sensors enabled

```
[sensor:125]: 'jnge-wind-solar-hybrid status battery voltage': Sending state 14.70000 V with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status pv voltage': Sending state 0.00000 V with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status fan voltage': Sending state 14.90000 V with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status pv charging current': Sending state 0.00000 A with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status fan charging current': Sending state 0.90000 A with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status pv charging power': Sending state 0.00000 W with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status fan charging power': Sending state 13.00000 W with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status pv total energy': Sending state 0.00000 kWh with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status fan total energy': Sending state 0.00000 kWh with 1 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status operation mode id': Sending state 0.00000  with 0 decimals of accuracy
[text_sensor:067]: 'jnge-wind-solar-hybrid status operation mode': Sending state 'Not charging'
[binary_sensor:036]: 'jnge-wind-solar-hybrid status load detected': Sending state OFF
[sensor:125]: 'jnge-wind-solar-hybrid status firmware version': Sending state 2.00000  with 0 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status peak pv charging rating': Sending state 0.00000 W with 0 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status peak fan charging rating': Sending state 0.00000 W with 0 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status battery strings': Sending state 1.00000  with 0 decimals of accuracy
[text_sensor:067]: 'jnge-wind-solar-hybrid status battery type': Sending state 'Custom'
[sensor:125]: 'jnge-wind-solar-hybrid status battery voltage level': Sending state 12.00000 V with 0 decimals of accuracy
[sensor:125]: 'jnge-wind-solar-hybrid status error bitmask': Sending state 16384.00000  with 0 decimals of accuracy
[text_sensor:067]: 'jnge-wind-solar-hybrid status errors': Sending state 'PV array undervoltage'
[binary_sensor:036]: 'jnge-wind-solar-hybrid status charging': Sending state ON
[binary_sensor:036]: 'jnge-wind-solar-hybrid status load': Sending state OFF
[switch:037]: 'jnge-wind-solar-hybrid config street light mode': Sending state OFF
[switch:037]: 'jnge-wind-solar-hybrid config charging': Sending state OFF
[switch:037]: 'jnge-wind-solar-hybrid config load': Sending state OFF
```

## Known issues

* A command queue would be nice

## Missing features

* Schedule configuration retrieval polling interval independent ([#3][i3])
* Register service to change the device configuration ([#4][i4])

[i3]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/3
[i4]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/4
