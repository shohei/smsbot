#include <SoftwareSerial.h>
#include <String.h>
#include <ArduinoJson.h>

SoftwareSerial mySerial(7, 8);

String recipientNumber[3];
char recv;

//  shohei:
//  AT+CMGS="+233241943721"
//  stephen:
//  AT+CMGS="+233274803438"
//  douglas:
//  AT+CMGS="+233245511543"

void setup()
{
  mySerial.begin(19200);               // the GPRS baud rate
  Serial.begin(19200);    // the GPRS baud rate
  while (!Serial) {
    // wait serial port initialization
  }
  delay(500);
}

void loop()
{
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
  SendTextMessage(tel, message);
  delay(3000);
}

///SendTextMessage()
///this function is to send a sms message
void SendTextMessage(String phoneNumber, String message)
{
  mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  String command = "AT + CMGS = \"" + phoneNumber + "\"";
  mySerial.println(command);//send sms message, be careful need to add a country code before the cellphone number
  delay(100);
  mySerial.println(message);//the content of the message
  delay(100);
  mySerial.println();
  delay(100);
  mySerial.write(0x1A);
  delay(100);
  mySerial.println();
}

void ShowSerialData()
{
  while (mySerial.available() != 0)
    Serial.write(mySerial.read());
}
