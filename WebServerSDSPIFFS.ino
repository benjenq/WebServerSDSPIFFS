/*  ESP32 / ESP8266 WebServer Sample: Control built-In LED from webpage which located on SPIFFS or external SD card.  
 *  
 *  - Device Requirement -
 *  Chip module base on ESP32 or ESP8266 with support LED_BUILTIN. Ex: 
 *   - NodeMCU, WEMOS D1/mini, base on ESP8266 chip.
 *   - NodeMCU-32S base on ESP32 chip. 
 *  
 *  - How to work ? -
 *
 *  0. Only for ESP32 users: Download library "WebServer_tng" and install in ~/Documents/Arduino/libraries
 *  https://github.com/bbx10/WebServer_tng
 *
 *  1. Fill up your wifi parameter "ssid" and "password" related to your network enviroment.
 *  2. Choose one from SPIFFS or SD Card Reader:
 *     Mark or Unmark "#define USE_SPIFFS" in BeSD_SPIFFS.h (Line 36)
 *     See header comment in BeSD_SPIFFS.h
 *  3. Build and upload the firmware to ESP8266 or ESP32 module with Arduino IDE.
 *  4. Use web browser to connect to this webserver ( http://esp32webserver.local for ESP32 module, or http://esp32webserver.local for ESP8266 module ).
 *  5. Done.
*/
const char* ssid     = "........"; //your ssid
const char* password = "........"; //your passwd


#include "BeWifi.h"
#include "BeWebServer.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  BeWifiSetup();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi is NOT connected, abort...");
    return;
  }
  BeWebServer_Setup();

  if(!Be_SpaceMounted()){
      digitalWrite(LED_BUILTIN, HIGH);
      return;
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  BeWifiLoop();
  BeWebServer_Loop();
}
