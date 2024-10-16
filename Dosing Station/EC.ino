#include "DFRobot_EC.h"
#include <EEPROM.h>

#define EC_PIN A2
float voltageEC, ecValue, temperature = 25;  // Temperature is set to a default of 25°C (you can update this with your actual temp sensor)
DFRobot_EC ec;

void setup()
{
    Serial.begin(115200);  
    ec.begin();  // Initialize the EC sensor
}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis() - timepoint > 1000U)  // Time interval: 1s
    {
        timepoint = millis();
        voltageEC = analogRead(EC_PIN) / 1024.0 * 5000;  // Read the EC sensor voltage
        ecValue = ec.readEC(voltageEC, temperature);     // Convert the voltage to EC with temperature compensation
        Serial.print("EC: ");
        Serial.print(ecValue, 2);  // Print EC value
        Serial.println(" ms/cm");
    }
}
