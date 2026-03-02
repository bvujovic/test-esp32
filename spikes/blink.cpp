#include <Arduino.h>

const int pin = 2; // 8 - C3 SuperMini, 1 - Dev, 22 - w/ battery connector

void setup()
{
  pinMode(pin, OUTPUT);
  // Serial.begin(115200);
  // digitalWrite(pin, false);
  // while (true)
  //   delay(100);
  // Serial.println(ESP.getFreeHeap() / 1024);
}

auto i = 1;

void loop()
{
  digitalWrite(pin, false);
  // Serial.println("false");
  delay(2000);
  digitalWrite(pin, true);
  // Serial.println("true");
  delay(2000);

  if (i++ >= 3)
    ESP.deepSleep(10 * 1000000UL); // sleep for 10 seconds
}