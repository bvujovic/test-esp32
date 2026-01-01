#include <Arduino.h>

const int pin = 2;
// const int pin = 8; // super mini ESP32

void setup()
{
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
  // digitalWrite(pin, false);
  // while (true)
  //   delay(100);
  Serial.println(ESP.getFreeHeap() / 1024);
}

void loop()
{
  digitalWrite(pin, true);
  Serial.println("true");
  delay(1000);
  digitalWrite(pin, false);
  Serial.println("false");
  delay(1000);
}