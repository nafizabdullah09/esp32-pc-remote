// 1. Your specific Blynk Device Info (Get these from blynk.cloud)
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID_HERE"
#define BLYNK_TEMPLATE_NAME "PC Remote"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN_HERE"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiUdp.h>

// 2. Your Wi-Fi network details
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// 3. Your Target PC's MAC Address formatted for Arduino
// Replace with the MAC address of the PC you want to wake up
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 

WiFiUDP udp;

// Stability Timer Variables
unsigned long lastRestartTime = 0;
const unsigned long restartInterval = 86400000; // 24 hours in milliseconds

void wakeMyPC() {
  udp.beginPacket(IPAddress(255, 255, 255, 255), 9);
  
  // Send the "Magic Packet" sequence
  for (int i = 0; i < 6; i++) udp.write(0xFF);
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 6; j++) {
      udp.write(mac[j]);
    }
  }
  udp.endPacket();
  Serial.println("Magic Packet Sent via Blynk!");
}

// This function listens to the Virtual Pin V0 in your Blynk App
BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Get value from the app button
  if (pinValue == 1) {
    // Button was pressed
    wakeMyPC();
  }
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi and Blynk Cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Record the time the ESP32 started
  lastRestartTime = millis();
}

void loop() {
  // Keep the connection to Blynk alive
  Blynk.run();
  
  // The 24/7 Stability Trick: Check if 24 hours have passed
  if (millis() - lastRestartTime > restartInterval) {
    Serial.println("Performing scheduled 24-hour reboot for memory stability...");
    ESP.restart(); // Forces the ESP32 to reboot
  }
}
