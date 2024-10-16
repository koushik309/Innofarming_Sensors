
# ESP32 Sensor Integration and Home Automation for Fluid Dosing Control

This repository contains the codebase for integrating various sensors with the ESP32, and the automation scripts for Home Assistant to control a fluid dosing system. It focuses on monitoring and managing critical environmental parameters, such as electrical conductivity (EC) and pH, using DFrobot sensors.

## Key Features

- **ESP32 Sensor Integration**:  
  Code to interface the ESP32 microcontroller with multiple sensors including EC and pH sensors via UART communication.
  
- **Fluid Dosing Control System**:  
  Logic for controlling peristaltic pumps to automatically regulate pH and EC levels in a fluid system. The system uses MQTT to communicate with Home Assistant and manage the dosing operations.
  
- **Home Assistant Automation**:  
  Custom automation scripts for integrating sensor data into Home Assistant, enabling real-time monitoring and alert systems for water quality.
  
- **Relay Control**:  
  Code to control relays that operate the motors for fluid dosing based on sensor values.
  
- **MQTT Communication**:  
  Seamless communication between ESP32 and Home Assistant using the MQTT protocol for sensor data updates and automation triggers.

## Folder Structure

├── esp32-sensors │ ├── ec_sensor.ino # Code for EC sensor integration │ ├── ph_sensor.ino # Code for pH sensor integration │ ├── mqtt_communication.ino # Code to handle MQTT communication │ └── relay_control.ino # Relay control logic ├── home-assistant │ ├── automation.yaml # Home Assistant automation script for fluid dosing │ ├── mqtt_sensors.yaml # MQTT sensor integration with Home Assistant └── README.md


## Prerequisites

- ESP32 microcontroller
- DFrobot EC and pH sensors
- Home Assistant instance
- MQTT broker (e.g., Mosquitto)
- Peristaltic pumps and relays for fluid dosing


