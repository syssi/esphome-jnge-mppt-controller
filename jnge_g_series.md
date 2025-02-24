# JN-G Series Pure Sine Wave Inverter

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

## Supported devices

* JN-G1000 Pure Sine Wave Inverter
* JN-G1500 Pure Sine Wave Inverter
* JN-G2000 Pure Sine Wave Inverter
* JN-G3000 Pure Sine Wave Inverter
* JN-G4000 Pure Sine Wave Inverter
* JN-G5000 Pure Sine Wave Inverter
* JN-G6000 Pure Sine Wave Inverter

## Schematics

```
                  RS485                      UART
┌────────────┐              ┌──────────┐                ┌─────────┐
│            │              │          │<----- RX ----->│         │
│    JNGE    │<-----B- ---->│  RS485   │<----- TX ----->│ ESP32/  │
│  G-series  │<---- A+ ---->│  to TTL  │<----- GND ---->│ ESP8266 │
│  inverter  │<--- GND ---->│  module  │<----- 3.3V --->│         │<-- VCC
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

or just use the `esp32-example-jnge-g-series.yaml` / `esp8266-example-jnge-g-series.yaml` as proof of concept:

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
esphome run esp32-example-jnge-g-series.yaml
```

If you use Home Assistant please uncomment the native `api` component and remove the `mqtt` section!

## Example response all sensors enabled

```
[I][jnge_g_series:044]: Status frame received (76 bytes)
[D][jnge_g_series:051]: Status Byte  0- 1:  4352 (0x1100)
[D][jnge_g_series:051]: Status Byte  2- 3:  6021 (0x1785)
[D][jnge_g_series:051]: Status Byte  6- 7:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 12-13:     1 (0x0001)
[D][jnge_g_series:051]: Status Byte 18-19:   207 (0x00CF)
[D][jnge_g_series:051]: Status Byte 20-21:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 22-23:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 24-25:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 26-27:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 28-29:     3 (0x0003)
[D][jnge_g_series:051]: Status Byte 30-31: 40951 (0x9FF7)
[D][jnge_g_series:051]: Status Byte 34-35:  3377 (0x0D31)
[D][jnge_g_series:051]: Status Byte 38-39:     4 (0x0004)
[D][jnge_g_series:051]: Status Byte 40-41:     3 (0x0003)
[D][jnge_g_series:051]: Status Byte 42-43:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 44-45: 65056 (0xFE20)
[D][jnge_g_series:051]: Status Byte 46-47:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 48-49:     1 (0x0001)
[D][jnge_g_series:051]: Status Byte 50-51:  1000 (0x03E8)
[D][jnge_g_series:051]: Status Byte 52-53:  2300 (0x08FC)
[D][jnge_g_series:051]: Status Byte 54-55:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 56-57:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 58-59:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 60-61:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 62-63:    34 (0x0022)
[D][jnge_g_series:051]: Status Byte 64-65:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 66-67:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 68-69:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 70-71:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 72-73:     0 (0x0000)
[D][jnge_g_series:051]: Status Byte 74-75:     0 (0x0000)
[D][sensor:098]: 'jn-g status AC voltage1': Sending state 230.00000 V with 1 decimals of accuracy
[D][sensor:098]: 'jn-g status AC voltage2': Sending state 230.50000 V with 1 decimals of accuracy
[D][sensor:098]: 'jn-g status AC frequency': Sending state 49.99000 Hz with 2 decimals of accuracy
[I][jnge_g_series:057]: Unknown 14:   73
[D][sensor:098]: 'jn-g status battery voltage': Sending state 13.40000 V with 1 decimals of accuracy
[D][sensor:098]: 'jn-g status total energy': Sending state 337.70001 kWh with 1 decimals of accuracy
[D][sensor:098]: 'jn-g status inverter temperature': Sending state 16.70000 °C with 1 decimals of accuracy

[I][jnge_g_series:070]: Config frame received (82 bytes)
[D][jnge_g_series:073]: Config Byte  0- 1:  4352 (0x1100)
[D][jnge_g_series:073]: Config Byte  2- 3:  6021 (0x1785)
[D][jnge_g_series:073]: Config Byte  4- 5:   142 (0x008E)
[D][jnge_g_series:073]: Config Byte  6- 7:   141 (0x008D)
[D][jnge_g_series:073]: Config Byte  8- 9:   144 (0x0090)
[D][jnge_g_series:073]: Config Byte 10-11:   141 (0x008D)
[D][jnge_g_series:073]: Config Byte 12-13:   135 (0x0087)
[D][jnge_g_series:073]: Config Byte 14-15:   140 (0x008C)
[D][jnge_g_series:073]: Config Byte 16-17:   104 (0x0068)
[D][jnge_g_series:073]: Config Byte 18-19:   103 (0x0067)
[D][jnge_g_series:073]: Config Byte 20-21:   102 (0x0066)
[D][jnge_g_series:073]: Config Byte 22-23:     1 (0x0001)
[D][jnge_g_series:073]: Config Byte 24-25:     3 (0x0003)
[D][jnge_g_series:073]: Config Byte 26-27:     4 (0x0004)
[D][jnge_g_series:073]: Config Byte 28-29:     3 (0x0003)
[D][jnge_g_series:073]: Config Byte 30-31:     6 (0x0006)
[D][jnge_g_series:073]: Config Byte 32-33: 40951 (0x9FF7)
[D][jnge_g_series:073]: Config Byte 34-35:  1750 (0x06D6)
[D][jnge_g_series:073]: Config Byte 36-37:  1800 (0x0708)
[D][jnge_g_series:073]: Config Byte 38-39:  2550 (0x09F6)
[D][jnge_g_series:073]: Config Byte 40-41:  2450 (0x0992)
[D][jnge_g_series:073]: Config Byte 42-43:   122 (0x007A)
[D][jnge_g_series:073]: Config Byte 44-45:   120 (0x0078)
[D][jnge_g_series:073]: Config Byte 46-47:     1 (0x0001)
[D][jnge_g_series:073]: Config Byte 48-49:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 50-51:     1 (0x0001)
[D][jnge_g_series:073]: Config Byte 52-53:   500 (0x01F4)
[D][jnge_g_series:073]: Config Byte 54-55:   300 (0x012C)
[D][jnge_g_series:073]: Config Byte 56-57:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 58-59:  4595 (0x11F3)
[D][jnge_g_series:073]: Config Byte 60-61:   132 (0x0084)
[D][jnge_g_series:073]: Config Byte 62-63:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 64-65:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 66-67:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 68-69:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 70-71:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 72-73:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 74-75:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 76-77:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 78-79:     0 (0x0000)
[D][jnge_g_series:073]: Config Byte 80-81:     0 (0x0000)

```

## Known issues

* A command queue would be nice

## Missing features / Limitations

* Many Modbus registers are not yet identified and their meaning is unknown
* Configuration registers cannot be decoded or modified yet
