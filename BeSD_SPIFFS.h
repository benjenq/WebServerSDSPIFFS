/*  Choose one from SPIFFS or SD Card Reader: 
 *  
 *  For SPIFFS users:
 *  Use "Sketch Data Upload" tools to upload all files data\*.* to SPIFFS. 
 *  - ESP8266
 *  "ESP8266 Sketch Data Upload" tool - Download
 *  https://github.com/esp8266/arduino-esp8266fs-plugin/releases
 *  
 *  - ESP32
 *  "ESP32 Sketch Data Upload" tool - Download
 *  https://github.com/me-no-dev/arduino-esp32fs-plugin/releases
 *
 *  How to install: (ESP8266 / ESP32 both the same)
 *  https://github.com/me-no-dev/arduino-esp32fs-plugin
 * 
 *  For SD card users:
 *  
 *  1. Format SD card with FAT32 type on PC , and copy all files data\*.* to SD root directory.
 *  2. Attach the SD card to the following pins:
 *
 *  SD Card   |   ESP32     |    ESP8266
 *   D2           -
 *   D3(CS)       SS (5)         NodeMCU: D8 (15)
 *   CMD(DI)      MOSI (23)      NodeMCU: D7 (13)
 *   VSS          GND            GND
 *   VDD          3.3V           3.3V
 *   CLK          SCK (18)       NodeMCU: D5 (14)
 *   VSS          GND            GND
 *   D0(MISO)     MISO (19)      NodeMCU: D6 (12)
 *   D1           -
 *   
*/
#ifndef BESD_SPIFFS_H
#define BESD_SPIFFS_H

//#define USE_SPIFFS  // <--- Mark with "//" for use SD Card. Remove "//" (unmark) to use SPIFFS.

#ifdef USE_SPIFFS
 #if defined(ESP32)
  #include <SPIFFS.h>
 #endif
 #include <FS.h>
#else //Use SD Card
 #include <SPI.h>
 #include <SD.h>
#endif

bool Be_SpaceMounted();

bool Be_SpaceMounted() {
#ifdef USE_SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS mount Failed, abort...");
    digitalWrite(LED_BUILTIN, HIGH);
    return false;
  }
  Serial.println("SPIFFS mount Successfully.");
  return true;
#else //SD Card
  if (!SD.begin()) {
    Serial.println("SD card mount Failed, abort...");
    return false;
  }
  Serial.println("SD card mount Successfully.");
  
#if defined(ESP32)
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return false;
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
#endif //ESP32

  return true;
#endif //USE_SPIFFS
}

#endif
