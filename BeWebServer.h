#ifndef BEWERSERVER_H
#define BEWERSERVER_H

#if defined(ESP8266)
  //#include <ESP8266WebServer.h>
  //ESP8266WebServer webserver(80);
#elif defined(ESP32)
  //#include <WebServer.h>
  //WebServer webserver(80);
#endif

#include "ESPAsyncWebServer.h"
AsyncWebServer webserver(80);

#include "BeWebServer_Handle.h"

void BeWebServer_Setup() {
  /*
  webserver.on("/mcuname",HTTP_GET, []() {
    String jsonResult = "{code:0,result:\"" + String(mcuName) + "\"}";
    webserver.send(200, "text/plain", jsonResult);
  });
  */
  webserver.on("/mcuname",HTTP_GET, handleMcuName);
  webserver.on("/buildled", HTTP_GET, handleBuiltinLed);
  webserver.onNotFound(handleNotFound);
  webserver.begin();
  Serial.print(F("HTTP server started.\nYou can connect to http://"));
  Serial.print(serverName);
  Serial.println(F(".local within web browser from any device"));
}

void BeWebServer_Loop() {
  //webserver.handleClient();
}


#endif
