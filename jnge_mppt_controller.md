# JN-MPPT Buck Solar Charge Controller

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

## Supported devices

* JN-MPPT-MINI Buck Solar Charge Controller `<2021/01: 12V / 24V / 48V`
* JN-MPPT-MINI Buck Solar Charge Controller `>=2021/01: 12V / 24V`
* JN-MPPT-AL Buck Solar Charge Controller
* JN-MPPT-BL Buck Solar Charge Controller
* JN-MPPT-CL Buck Solar Charge Controller

The manufacturer dropped the 48V support of the JN-MPPT-MINI in 2021. The new and downgraded model can be identified by a white sticker:

```
JN-MPPT_MINI
V:21/24V
C:30A
P:360/720W
2021/04/29
```

## Schematics

<a href="https://raw.githubusercontent.com/syssi/esphome-jnge-mppt-controller/main/images/circuit.jpg" target="_blank">
<img src="https://raw.githubusercontent.com/syssi/esphome-jnge-mppt-controller/main/images/circuit_thumbnail.jpg" width="50%">
</a>

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

#### Old pinout (< 2021/05)

| Pin     | Purpose      | RS485-to-TTL pin  | Color T-568B |
| :-----: | :----------- | :---------------- | ------------ |
|  **1**  | **B-**       | **B-**            | Orange-White |
|    2    | B-           |                   |              |
|  **3**  | **A+**       | **A+**            | Green-White  |
|    4    | A+           |                   |              |
|  **5**  | **GND**      | **GND**           | Blue-White   |
|    6    | GND          |                   |              |
|    7    | +12V         |                   | Brown-White  |
|    8    | +12V         |                   |              |

#### New pinout (> 2022/11)

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

If you use Home Assistant please uncomment the native `api` component and remove the `mqtt` section!

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

![Lovelace entities card](lovelace-entities-card.png "Lovelace entities card")

## Known issues

* A command queue would be nice

## Missing features

* Schedule configuration retrieval polling interval independent ([#3][i3])
* Register service to change the device configuration ([#4][i4])

[i3]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/3
[i4]: https://github.com/syssi/esphome-jnge-mppt-controller/issues/4
