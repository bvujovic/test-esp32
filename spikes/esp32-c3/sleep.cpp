// 1: blue board with yellow pin headers and antenna connector
// 2: black board with short red antenna
//
// Board    Normal   Deep Sleep (with power LED on)
// 1        19.2mA   2.8mA
// 2        17.8mA   0.88mA

#include <Arduino.h>

void setup()
{
    delay(5000);            // Wait for 5 seconds before starting
    ESP.deepSleep(5000000); // Put the ESP32 into deep sleep for 5 seconds
}

void loop() { }
