#ifndef BEWEBSERVER_HANDLE_H
#define BEWEBSERVER_HANDLE_H

#include "BeSD_SPIFFS.h"

/* Function Define */
void serverSend(int num, const char * datatype, String message);
void handleNotFound();
bool handleFileRead(String path);
String getContentType(String filename);
void handleMcuName();
void handleBuiltinLed();

/* Function implement */

void serverSend(int num, const char * datatype, String message) {
  webserver.sendHeader("Access-Control-Allow-Origin", "*"); //Allow any resource to access message content. Google-Chrome required.
  webserver.send(num, datatype, message + "\r\n");
}

void handleMcuName() {
  String jsonResult = "{\"code\":0,\"result\":\"" + String(mcuName) + "\"}";
  serverSend(200, "text/plain", jsonResult);
}

void handleBuiltinLed() {
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);
  serverSend(200, "text/plain", "{\"code\":0, \"result\":\"OK\"}");
}

void handleNotFound() {
  if (!handleFileRead(webserver.uri())) {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += webserver.uri();
    message += "\nMethod: ";
    message += (webserver.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += webserver.args();
    message += "\n";
    for (uint8_t i = 0; i < webserver.args(); i++) {
      message += " " + webserver.argName(i) + ": " + webserver.arg(i) + "\n";
    }
    serverSend(404, "text/plain", message);
  }
}

bool handleFileRead(String path) {

  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path);

  // Handle .gz file
  String pathWithGz = path + ".gz";
#ifdef USE_SPIFFS
  if (SPIFFS.exists(path) || SPIFFS.exists(pathWithGz)) {
    if (SPIFFS.exists(pathWithGz)) { //Check if .gz file exist
      path += ".gz";
    }
    File file = SPIFFS.open(path, "r");
#else
  if (SD.exists(path) || SD.exists(pathWithGz)) {
    if (SD.exists(pathWithGz)) { //Check if .gz file exist
      path += ".gz";
    }
    File file = SD.open(path);
#endif
    Serial.println("handleFileRead: " + path);
    webserver.streamFile(file, contentType);
    file.close();
    return true;
  }

  return false;
}

String getContentType(String filename) {
  if (webserver.hasArg("download")) return "application/octet-stream";
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
