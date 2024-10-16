
# Workflow Documentation for ESP32 with MQTT and UART-Based pH and EC Control

This documentation provides a step-by-step explanation of how the ESP32 communicates with both **Home Assistant** (via MQTT) and an **Arduino** (via UART) to control relays based on pH and EC values. The primary goal is to automatically control the dosing system for pH and EC levels using the data provided by sensors and user-defined values from Home Assistant.

---

## 1. System Overview

- **ESP32**: Acts as the central controller, handling data from both Home Assistant (via MQTT) and the Arduino (via UART). It controls relays that activate the dosing pumps for adjusting pH and EC levels.
- **Home Assistant**: Provides the user interface where users can set desired minimum and maximum EC values via sliders. These values are sent to the ESP32 via MQTT.
- **Arduino**: Reads pH and EC sensor data and sends these values to the ESP32 over a UART connection.
- **Relays**: Connected to the ESP32, they control the peristaltic pumps that adjust pH and EC levels in water. The relays are activated when the current EC or pH values fall outside the desired range.

---

## 2. Components Involved

- **ESP32**: Handles MQTT communication with Home Assistant, receives pH and EC sensor values over UART from Arduino, and controls the relays.
- **Home Assistant**: Provides EC and pH range control via MQTT topics and UI sliders.
- **Arduino**: Reads pH and EC sensor data and transmits the values to the ESP32 over UART.
- **pH and EC Sensors**: Measure water pH and EC levels.
- **Relays**: Connected to dosing pumps to control pH and EC levels based on ESP32 decisions.

---

## 3. Workflow Breakdown

### Step 1: Initial Setup

#### Wi-Fi Connection
1. When powered on, the ESP32 first connects to the Wi-Fi network using credentials specified in the code. This connection is necessary for communicating with the MQTT broker hosted by Home Assistant.

#### MQTT Connection
1. After connecting to Wi-Fi, the ESP32 establishes a connection with the MQTT broker (in Home Assistant).
2. It subscribes to two topics:
   - `setDosingmin`: Receives the minimum EC value from Home Assistant.
   - `setDosingmax`: Receives the maximum EC value from Home Assistant.

#### UART Communication Setup
1. The ESP32 initializes the UART connection to the Arduino on **GPIO16 (RX)** and **GPIO17 (TX)** at a baud rate of 9600.
2. The Arduino continuously sends pH and EC sensor data over this UART connection.

---

### Step 2: Receiving pH and EC Data from Arduino

#### Sensor Data Over UART
1. The Arduino reads the pH and EC sensor values and sends them to the ESP32 in **CSV format** (e.g., `7.0,1.5\n`). The data is transmitted every second.

#### ESP32 Parses the Data
1. The ESP32 reads the incoming string from UART, splits the string into pH and EC values, and stores them in the `phValue` and `ecValue` variables.

#### Debugging/Verification
1. The parsed pH and EC values are printed to the **Serial Monitor** for debugging purposes.

---

### Step 3: Receiving User-Defined EC Ranges from Home Assistant (via MQTT)

#### MQTT Messages
1. Home Assistant sends user-defined minimum (`setDosingmin`) and maximum (`setDosingmax`) EC values as MQTT messages when the user adjusts the sliders in the Home Assistant interface.

#### Handling MQTT Messages
1. The ESP32 receives these messages and stores the values in `ecMin` and `ecMax`.

#### Debugging/Verification
1. The ESP32 prints the updated EC min and max values to the **Serial Monitor** for debugging purposes.

---

### Step 4: Comparison Logic and Relay Activation

#### Comparison of EC Values
1. After receiving the current EC value from the sensor via UART and the desired EC range from MQTT, the ESP32 compares the current EC value with `ecMin` and `ecMax`.
2. If the current EC value is outside the specified range (either lower than `ecMin` or higher than `ecMax`), the ESP32 triggers the EC relay.

#### Relay Activation
1. The relay connected to the **EC dosing pump** is activated for 30 seconds if the EC value is outside the desired range.
2. For pH control (not fully implemented in this example), a similar comparison and activation logic could be used.

#### Relay Deactivation
1. After the 30-second activation period, the relay is turned off, and the system resumes monitoring.

---

### Step 5: Rechecking the Values

#### Continuous Monitoring
1. The ESP32 continuously receives sensor data from the Arduino and compares it against the user-defined range.
2. If the EC values still fall outside the range after the relay has been triggered, the relay will be triggered again, ensuring that the system maintains the desired EC levels.

---

## 4. Detailed Code Explanation

### Wi-Fi and MQTT Setup
1. The function `setup_wifi()` connects the ESP32 to the Wi-Fi network.
2. The `reconnect()` function ensures that the ESP32 remains connected to the MQTT broker and resubscribes to the required topics.

### UART Setup
1. The UART interface is initialized using the `HardwareSerial` library to establish communication with the Arduino over **GPIO16 (RX)** and **GPIO17 (TX)**.
2. The `readSensors()` function reads the pH and EC values from the Arduino, parses them, and stores them in the `phValue` and `ecValue` variables.

### Receiving and Handling MQTT Messages
1. The callback function `callback()` is triggered whenever a new message is received on the MQTT topics `setDosingmin` or `setDosingmax`.
2. The payload is converted to a float and stored in `ecMin` or `ecMax`.

### Comparison and Relay Control
1. The `if` statement in the `loop()` function compares the current EC value with the user-defined range (`ecMin` and `ecMax`).
2. If the value is outside the range, the relay connected to the dosing pump is activated for 30 seconds.

---

## 5. System Testing and Verification

### Serial Monitor Debugging
1. All sensor values, MQTT messages, and relay activations are printed to the **Serial Monitor** to verify correct functionality.

### Home Assistant Interaction
1. Test the system by adjusting the EC sliders in the Home Assistant interface. When the EC value is outside the set range, the relays should activate accordingly.

### Manual Testing
1. You can manually adjust the EC and pH values and observe how the ESP32 responds by turning the dosing pumps on and off.

---

## 6. Potential Future Enhancements

### Add pH Control
1. Implement similar logic for pH control by adding MQTT topics for pH min and pH max and comparing the pH sensor value accordingly.

### Real-Time Data Feedback
1. Implement additional MQTT publishing functionality to send the current sensor readings (pH and EC) back to Home Assistant, allowing for real-time monitoring of water conditions on the Home Assistant dashboard.

### Temperature Compensation
1. Incorporate a temperature sensor to compensate for the pH and EC readings for temperature fluctuations.

---

This document outlines the workflow for how the ESP32 interacts with Home Assistant, the Arduino, and relays to maintain the water’s pH and EC levels within the desired range.
