### Use SPIFFS or SD card 
---
#### For SPIFFS users:<br>
Use "Sketch Data Upload" tools to upload all files data\\\*.\* to SPIFFS.<br>
- **ESP8266** <br>
  "ESP8266 Sketch Data Upload" tool - Download<br>
  https://github.com/esp8266/arduino-esp8266fs-plugin/releases<br>
  
- **ESP32**<br>
  "ESP32 Sketch Data Upload" tool - Download<br>
  https://github.com/me-no-dev/arduino-esp32fs-plugin/releases<br>

**How to install Sketch Data Upload tool** (ESP8266 / ESP32 both the same)<br>
  https://github.com/me-no-dev/arduino-esp32fs-plugin
 
#### For SD card users:<br>
  1. Format SD card with FAT32 type on PC , and copy all files data\\\*.\* to SD root directory.
  2. Attach the SD card to the following pins:
 
  |  SD Card   |   ESP32(GPIO)    |    ESP8266(GPIO) |
  |  :----      |  :----       | :----       |
  |  D2        |   -         |            
  | D3(CS)     |  SS (5)     | NodeMCU: D8 (15) |
  | CMD(DI)    | MOSI (23)   |  NodeMCU: D7 (13) |
  | VSS        | GND         |  GND |
  | VDD        | 3.3V        |  3.3V |
  | CLK        | SCK (18)    |  NodeMCU: D5 (14) |
  | VSS        | GND         |  GND |
  | D0(MISO)   | MISO (19)   |  NodeMCU: D6 (12) |
  | D1         | -           |      |
  
    
