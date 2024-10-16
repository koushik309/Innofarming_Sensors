# ESP32 Sensor Integration and Home Automation for Fluid Dosing Control
This repository contains the codebase for integrating various sensors with the ESP32, and the automation scripts for Home Assistant to control a fluid dosing system. It focuses on monitoring and managing critical environmental parameters, such as electrical conductivity (EC) and pH, using DFrobot sensors.

Key Features
ESP32 Sensor Integration: Code to interface the ESP32 microcontroller with multiple sensors including EC and pH sensors via UART communication.
Fluid Dosing Control System: Logic for controlling peristaltic pumps to automatically regulate pH and EC levels in a fluid system. The system uses MQTT to communicate with Home Assistant and manage the dosing operations.
Home Assistant Automation: Custom automation scripts for integrating sensor data into Home Assistant, enabling real-time monitoring and alert systems for water quality.
Relay Control: Code to control relays that operate the motors for fluid dosing based on sensor values.
MQTT Communication: Seamless communication between ESP32 and Home Assistant using the MQTT protocol for sensor data updates and automation triggers.
This repository is designed to be a complete solution for those looking to automate fluid dosing systems in precision agriculture, hydroponics, or other water quality management systems.
