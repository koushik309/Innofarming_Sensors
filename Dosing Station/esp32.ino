#include <WiFi.h>
#include <PubSubClient.h>
#include <HardwareSerial.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your MQTT broker's IP address and port
const char* mqtt_server = "your_mqtt_broker_ip";
const int mqtt_port = 1883;  // Default MQTT port

// MQTT topics for receiving the EC min and max values
const char* topic_set_ecmin = "setDosingmin";
const char* topic_set_ecmax = "setDosingmax";

// Variables to store EC min and max values from MQTT
float ecMin = 0.0;
float ecMax = 0.0;

// pH and EC sensor values from UART
float phValue = 0.0;
float ecValue = 0.0;

// Pin definitions for relays
const int phRelayPin = 5;  // Change to the pin connected to pH relay
const int ecRelayPin = 4;  // Change to the pin connected to EC relay

// Create an instance for UART communication (HardwareSerial)
HardwareSerial mySerial(1);  // UART1 on GPIO16 (RX) and GPIO17 (TX)

WiFiClient espClient;
PubSubClient client(espClient);

// Function to connect to Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

// Callback function to handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String receivedMessage;
  
  // Convert payload to string
  for (int i = 0; i < length; i++) {
    receivedMessage += (char)payload[i];
  }

  // Remove any whitespace
  receivedMessage.trim();

  // Convert the received payload to float
  float value = receivedMessage.toFloat();

  // Check which topic the message is coming from and update the appropriate variable
  if (String(topic) == topic_set_ecmin) {
    ecMin = value;
    Serial.print("Received EC Min: ");
    Serial.println(ecMin);
  }
  else if (String(topic) == topic_set_ecmax) {
    ecMax = value;
    Serial.print("Received EC Max: ");
    Serial.println(ecMax);
  }
}

// Function to reconnect to the MQTT broker if the connection is lost
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe to the EC min and max topics
      client.subscribe(topic_set_ecmin);
      client.subscribe(topic_set_ecmax);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Function to read the pH and EC values from UART
void readSensors() {
  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');  // Read pH,EC data from Arduino
    data.trim();  // Remove any extra spaces
    int commaIndex = data.indexOf(',');
    if (commaIndex > 0) {
      // Extract pH and EC values from the UART string
      phValue = data.substring(0, commaIndex).toFloat();
      ecValue = data.substring(commaIndex + 1).toFloat();
      
      Serial.print("pH from sensor: ");
      Serial.println(phValue);
      Serial.print("EC from sensor: ");
      Serial.println(ecValue);
    }
  }
}

// Function to activate a relay for 30 seconds
void activateRelay(int relayPin) {
  digitalWrite(relayPin, HIGH);  // Activate the relay
  delay(30000);                  // Wait for 30 seconds
  digitalWrite(relayPin, LOW);   // Deactivate the relay
}

void setup() {
  Serial.begin(115200);  // Start the serial communication for debugging
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // Start UART communication with Arduino

  setup_wifi();  // Connect to WiFi
  
  client.setServer(mqtt_server, mqtt_port);  // Setup MQTT connection
  client.setCallback(callback);  // Set callback for receiving MQTT messages

  // Setup relay pins
  pinMode(phRelayPin, OUTPUT);
  pinMode(ecRelayPin, OUTPUT);

  digitalWrite(phRelayPin, LOW);  // Ensure relays are off initially
  digitalWrite(ecRelayPin, LOW);
}

void loop() {
  // Ensure the ESP32 stays connected to MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read pH and EC values from the sensors via UART
  readSensors();

  // Compare the sensor values with the MQTT set points and activate relays if needed
  if (ecValue < ecMin || ecValue > ecMax) {
    Serial.println("EC value is out of range, activating EC relay");
    activateRelay(ecRelayPin);  // Activate EC relay for 30 seconds
  }

  delay(2000);  // Delay for 2 seconds before the next loop
}
