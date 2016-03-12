// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#include <ArduinoJson.h>

void setup() {
  Serial.begin(19200);
  while (!Serial) {
    // wait serial port initialization
  }

//  char json[] =
//    "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

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

  //    while(!end){
  //      char c = Serial.read();
  //      if (c == '{') {
  //        begin = true;
  //      }
  //      if (begin) response += (c);
  //      if (c == '}') {
  //        end = true;
  //        break;
  //      }
  //      delay(1);
  //     }

  const char *charBuf = response.c_str();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(charBuf);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  const char* message = root["message"];
  const char* tel = root["tel"];
//  long time = root["time"];
//  double latitude = root["data"][0];
//  double longitude = root["data"][1];
  Serial.println(message);
  Serial.println(tel);
}


