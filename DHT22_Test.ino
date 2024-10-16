#include "DHT.h"

// Define the pin where the data line of the DHT22 is connected
#define DHTPIN 4  // Change this to the GPIO pin you're using (e.g., GPIO 4)

// Define the type of DHT sensor (DHT22)
#define DHTTYPE DHT22

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  
  // Start the DHT sensor
  dht.begin();
  
  Serial.println("DHT22 sensor test starting...");
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Read humidity and temperature as Celsius (the default)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // In Celsius
  
  // Check if any readings failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Read temperature as Fahrenheit
  float temperatureF = dht.readTemperature(true);
  
  // Print the readings to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C ");
  Serial.print(temperatureF);
  Serial.println(" °F");
}
