#include "DFRobot_PH.h"
#include "DFRobot_EC.h"
#include <EEPROM.h>

#define PH_PIN A1
#define EC_PIN A2

float voltagePH, voltageEC, phValue, ecValue, temperature = 25; // Default temp 25°C
DFRobot_PH ph;
DFRobot_EC ec;

void setup()
{
    Serial.begin(115200);  // UART communication for Serial Monitor
    Serial1.begin(9600);   // UART communication for ESP32 (use Serial1)
    ph.begin();            // Initialize the pH sensor
    ec.begin();            // Initialize the EC sensor
}

void loop()
{
    static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U)  // Time interval: 1s
    {
        timepoint = millis();
        voltagePH = analogRead(PH_PIN) / 1024.0 * 5000;  // Read the pH sensor voltage
        phValue = ph.readPH(voltagePH, temperature);     // Convert voltage to pH
        voltageEC = analogRead(EC_PIN) / 1024.0 * 5000;  // Read the EC sensor voltage
        ecValue = ec.readEC(voltageEC, temperature);     // Convert voltage to EC
        
        // Send pH and EC values over UART (Serial1)
        Serial1.print(phValue, 2);  // Send pH value (2 decimal places)
        Serial1.print(",");
        Serial1.println(ecValue, 2);  // Send EC value (2 decimal places)

        // Print values to Serial Monitor (optional for debugging)
        Serial.print("pH: ");
        Serial.print(phValue, 2);
        Serial.print(", EC: ");
        Serial.println(ecValue, 2);
    }
}
