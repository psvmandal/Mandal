#include "sonic.h"
#include "vibrationSensor.h"
#include "fs.h"  // Fuel sensor
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <WiFi.h>

const char* ssid = "POCO";       // WiFi SSID
const char* password = "12345678"; // WiFi Password

WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      Serial.printf("[%u] Connected!\n", num);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Connecting to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ss();  // Ultrasonic sensor
  vss(); // Vibration sensor
  fs();  // Fuel sensor

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  StaticJsonDocument<256> doc;
  float vibration, maxVibration;
  vsl(&vibration, &maxVibration); // Passing by reference
  float distance;
  bool motionDetected;
  sl(&distance, &motionDetected); // Passing by reference

  float fuelLevel, fuelPercentage;
  fl(&fuelLevel, &fuelPercentage); 

  doc["vibration"] = vibration;
  doc["maxVibration"] = maxVibration;
  doc["distance"] = distance;
  doc["motionDetected"] = motionDetected;
  doc["fuelLevel"] = fuelLevel;
  doc["fuelPercentage"] = fuelPercentage;
  doc["ip_address"] = WiFi.localIP().toString(); // Adding IP address to JSON

  String jsonString;
  serializeJson(doc, jsonString);

  webSocket.broadcastTXT(jsonString);
  delay(250);
}
