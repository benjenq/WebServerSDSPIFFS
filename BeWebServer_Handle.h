/*   Rewrite each method with add parameter "AsyncWebServerRequest *request" after use library ESPAsyncWebServer instead of official WebServer.h 
 *   Changed "webserver.xxxx" to "request->xxxx" for most situation.
 */
#ifndef BEWEBSERVER_HANDLE_H
#define BEWEBSERVER_HANDLE_H

#include "BeSD_SPIFFS.h"

/* Function Define */
void serverSend(int num, const char * datatype, String message, AsyncWebServerRequest *request);
void handleNotFound(AsyncWebServerRequest *request);
bool handleFileRead(String path, AsyncWebServerRequest *request);
String getContentType(String filename, AsyncWebServerRequest *request);
void handleMcuName(AsyncWebServerRequest *request);
void handleBuiltinLed(AsyncWebServerRequest *request);

/* Function implement */

void serverSend(int num, const char * datatype, String message, AsyncWebServerRequest *request) {
  AsyncWebServerResponse *response = request->beginResponse(num,datatype,message);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void handleMcuName(AsyncWebServerRequest *request) {
  String jsonResult = "{\"code\":0,\"result\":\"" + String(mcuName) + "\"}";
  serverSend(200, "text/plain", jsonResult, request);
}

void handleBuiltinLed(AsyncWebServerRequest *request) {
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);
#if defined(ESP8266)
  String ledState = state ? "On" : "Off";
#elif defined(ESP32)
  String ledState = state ? "Off" : "On";
#endif
  serverSend(200, "text/plain", "{\"code\":0, \"result\":\"" + ledState + "\"}", request);
}

void handleNotFound(AsyncWebServerRequest *request) { /* Replace webserver.xxxx with request->xxxx */
  if (!handleFileRead(request->url().c_str(), request)) {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += request->url().c_str();
    message += "\nMethod: ";
    message += (request->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += request->args();
    message += "\n";
    for (uint8_t i = 0; i < request->args(); i++) {
      message += " " + String(request->argName(i).c_str()) + ": " + request->arg(i).c_str() + "\n";
    }
    serverSend(404, "text/plain", message, request);
  }
}

bool handleFileRead(String path, AsyncWebServerRequest *request) {

  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path, request);

  // Handle .gz file
  String pathWithGz = path + ".gz";
#ifdef USE_SPIFFS
  if (SPIFFS.exists(path) || SPIFFS.exists(pathWithGz)) {
    if (SPIFFS.exists(pathWithGz)) { //Check if .gz file exist
      path += ".gz";
    }
    //File file = SPIFFS.open(path, "r");
#else
  if (SD.exists(path) || SD.exists(pathWithGz)) {
    if (SD.exists(pathWithGz)) { //Check if .gz file exist
      path += ".gz";
    }
    //File file = SD.open(path);
#endif

    Serial.println("handleFileRead: " + path);

#ifdef USE_SPIFFS
    request->send(SPIFFS, path, contentType); /* Replace webserver.streamFile(file, contentType) with request->send(SPIFFS, path, contentType) */
#else
    request->send(SD, path, contentType); /* Replace webserver.streamFile(file, contentType) with request->send(SD, path, contentType) */
#endif
    //file.close();
    return true;
  }

  return false;
}

String getContentType(String filename, AsyncWebServerRequest *request) {
  if (request->hasArg("download")) return "application/octet-stream"; /* Replace webserver.hasArg("download") with request->hasArg("download") */ 
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

#endif //BEWEBSERVER_HANDLE_H
