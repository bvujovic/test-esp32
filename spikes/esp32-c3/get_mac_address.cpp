//* 24:EC:4A:C8:A7:2C

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

void setup()
{
  Serial.begin(115200);
  // Serial.println("Test!");
  // Serial.print(WiFi.macAddress());
  //   Serial.print("\nESP Board MAC Address: " + WiFi.macAddress());
}

void loop()
{
  Serial.println(WiFi.macAddress());
  delay(1000);
}
