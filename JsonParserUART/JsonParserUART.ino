// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#include <ArduinoJson.h>

void setup() {
  Serial.begin(19200);
  while (!Serial) {
    // wait serial port initialization
  }

}

void loop() {
  String response;
  bool begin = false;
  bool end = false;

  while (!end) {
    if (Serial.available() > 0)
    {
      begin = true;
      response = Serial.readStringUntil('\n');
      Serial.println(response);
      end = true;
    }
  }

  const char *charBuf = response.c_str();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(charBuf);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  const char* message = root["message"];
  const char* tel = root["tel"];
  Serial.println(message);
  Serial.println(tel);
}


