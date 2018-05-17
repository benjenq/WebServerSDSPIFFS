#ifndef BEWIFI_H
#define BEWIFI_H

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
  const char* mcuName = "ESP8266";
  const char* serverName = "esp8266webserver";
#elif defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
  const char* mcuName = "ESP32";
  const char* serverName = "esp32webserver";
#else
  #error "This firmware ONLY support ESP32 / ESP8266 SoC Module"
#endif



void BeWifiSetup() {

  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F(""));
  Serial.print(F("WiFi connected. IP address: "));
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(serverName)) {
    Serial.println(F("Error setting up MDNS responder!"));
    while (1) {
      delay(1000);
      Serial.print("*");
    }
  }
  Serial.println(F("mDNS responder started."));

}

void BeWifiLoop() {

}

#endif //BEWIFI_H

