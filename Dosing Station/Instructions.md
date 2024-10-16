
# Hardware Setup

## Components Needed:
- Arduino Uno/Nano (or another Arduino model)
- ESP32
- pH Sensor (connected to Arduino)
- EC Sensor (connected to Arduino)
- Jumper wires

## Wiring Connections:

- **TX (Transmit) Pin of Arduino** to **RX (Receive) Pin of ESP32**:
    - If using Arduino Uno, TX is **Pin 1**.
    - On the ESP32, RX could be **GPIO16**.
  
- **RX (Receive) Pin of Arduino** to **TX (Transmit) Pin of ESP32**:
    - If using Arduino Uno, RX is **Pin 0**.
    - On the ESP32, TX could be **GPIO17**.
  
- **GND (Ground)**: Connect the GND of the Arduino to the GND of the ESP32 to ensure a common ground.

## Wiring Table:

| Arduino Pin | ESP32 Pin  |
| ----------- | ---------- |
| TX (Pin 1)  | RX (GPIO16)|
| RX (Pin 0)  | TX (GPIO17)|
| GND         | GND        |

