#include <HardwareSerial.h>

HardwareSerial mySerial(1);  // Use UART1 on ESP32 (TX on GPIO17, RX on GPIO16)

// MHZ19C command to request CO2 concentration
byte getCO2Command[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };

void setup() {
  // Start the serial communication with the ESP32 and the sensor
  Serial.begin(115200);  // Serial Monitor
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // Serial communication with MH-Z19C (TX=17, RX=16)
  
  Serial.println("MH-Z19C CO2 sensor test starting...");
}

void loop() {
  // Send the command to get CO2 concentration
  mySerial.write(getCO2Command, 9);
  
  // Wait for the sensor to respond (it takes a few milliseconds)
  delay(500);

  // Check if there are available bytes in the buffer
  if (mySerial.available() > 0) {
    byte response[9];
    
    // Read the 9-byte response from the sensor
    for (int i = 0; i < 9; i++) {
      response[i] = mySerial.read();
    }
    
    // Check if the response is valid
    if (response[0] == 0xFF && response[1] == 0x86) {
      // Calculate CO2 concentration from response bytes
      int co2 = (response[2] << 8) + response[3];
      
      // Print the CO2 concentration
      Serial.print("CO2 Concentration: ");
      Serial.print(co2);
      Serial.println(" ppm");
    } else {
      Serial.println("Invalid response from MH-Z19C sensor");
    }
  } else {
    Serial.println("No data received from MH-Z19C sensor");
  }
  
  // Wait for 2 seconds before the next reading
  delay(2000);
}
