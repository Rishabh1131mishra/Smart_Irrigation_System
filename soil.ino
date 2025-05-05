#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "dlink-F3CC";
const char* password = "87654321";

const int relayPin = 5; // GPIO5 corresponds to D1 on NodeMCU

const int sensor_pin = A0;   // Soil sensor input (analog)

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Relay initially off
  pinMode(sensor_pin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize OTA
  ArduinoOTA.begin();
}

void loop() {
  // Handle OTA updates
  ArduinoOTA.handle();

  // Read soil moisture from analog sensor
  int sensorValue = analogRead(sensor_pin);
  int moisturePercentage = map(sensorValue, 1023, 0, 0, 100); // Map to 0–100%

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Relay control based on moisture
  if (moisturePercentage < 10) {
    digitalWrite(relayPin, LOW); // Turn ON motor
    Serial.println("Motor ON");
  } else {
    digitalWrite(relayPin, LOW);  // Turn OFF motor
    Serial.println("Motor OFF");
  }

  delay(1000);
}
