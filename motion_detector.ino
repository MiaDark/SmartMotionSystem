#include <WiFi101.h>
#include <PubSubClient.h>
#include "credentials.h"

// MQTT broker settings
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_client_id = "MKR1000_MotionSensor";
const char* mqtt_topic = "home/motion/entry";

const int pirPin = 2;
int pirState = LOW;
unsigned long lastMotionTime = 0;
const unsigned long debounceDelay = 500; 


const int buzzerPin = 3;
const int diodePin = 4;


WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(diodePin, OUTPUT);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int newState = digitalRead(pirPin);
  unsigned long currentTime = millis();

  if (newState == HIGH && pirState == LOW && currentTime - lastMotionTime > debounceDelay) {
    Serial.println("Motion detected!");
    client.publish(mqtt_topic, "MOTION DETECTED");
    lastMotionTime = currentTime;
    pirState = HIGH;
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(diodePin, HIGH);
  } else if (newState == LOW && pirState == HIGH) {
    Serial.println("No motion!");
    pirState = LOW;
    digitalWrite(buzzerPin, LOW);
    digitalWrite(diodePin, LOW);
  }
}