# esphome-jnge-mppt-controller

![GitHub actions](https://github.com/syssi/esphome-jnge-mppt-controller/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-jnge-mppt-controller)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-jnge-mppt-controller)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-jnge-mppt-controller)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor and control a JN-MPPT or JN-W/S Controller via RS485

![Lovelace entities card](lovelace-entities-card.png "Lovelace entities card")

## Supported devices

* JN-MPPT-MINI Buck Solar Charge Controller
* JN-MPPT-AL Buck Solar Charge Controller
* JN-MPPT-BL Buck Solar Charge Controller
* JN-MPPT-CL Buck Solar Charge Controller
* JN-12-W300/S300, JN-12-W500/S500 Wind and Solar Hybrid Controller
* JN-24-W600/S600, JN-24-W800/S800 Wind and Solar Hybrid Controller
* JN-48-W800/S800, JN-48-W1000/S1000 Wind and Solar Hybrid Controller
* JN-G series (JN-G1000, JN-G1500, JN-G2000, ..., JN-G6000) Pure Sine Wave Inverter

## Requirements

* [ESPHome 2024.6.0 or higher](https://github.com/esphome/esphome/releases).
* One half of an ethernet cable with RJ45 connector
* RS485-to-TTL module (`HW-0519` f.e.)
* Generic ESP32 or ESP8266 board

## Setup

* [JN-MPPT Buck Solar Charge Controller](jnge_mppt_controller.md)
* [JN-W/S Wind and Solar Hybrid Controller](jnge_wind_solar_controller.md)
* [JN-G Pure Sine Wave Inverter](jnge_g_series.md)

## Debugging

If this component doesn't work out of the box for your device please update your configuration to enable the debug output of the UART component and increase the log level to the see outgoing and incoming serial traffic:

```
logger:
  level: DEBUG

uart:
  id: uart_0
  baud_rate: 9600
  tx_pin: ${tx_pin}
  rx_pin: ${rx_pin}
  debug:
    direction: BOTH
```

## References

* JNGE MPPT Controller Internal Communication Proto.pdf
* [JNGE Wind and Solar Hybrid Controller Internal Communication Proto.pdf](https://github.com/syssi/esphome-jnge-mppt-controller/files/8106839/JNGE.Wind.and.Solar.Hybrid.Controller.Internal.Co.pdf)
